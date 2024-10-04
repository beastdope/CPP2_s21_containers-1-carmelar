#include "s21_list.h"

namespace s21 {

// Итераторы
template <typename T> T &List<T>::Iterator::operator*() {
  return node_->data;
} // оператор разыменования

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  node_ = node_->next;
  return *this;
} // оператор инкремента

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
  if (node_) {
    node_ = node_->prev;
  }
  return *this;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &other) const {
  return node_ == other.node_;
}
template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &other) const {
  return node_ != other.node_;
}

// методы List

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), length(0) {}

template <typename T> List<T>::List(size_t n) : List() {
  for (size_t i = 0; i < n; ++i)
    push_back(T());
}

template <typename T> List<T>::List(const List &other) : List() { copy(other); }

template <typename T> List<T>::List(List &&other) noexcept : List() {
  swap(other);
}
template <typename T> List<T> &List<T>::operator=(List &&other) noexcept {
  if (this != &other) {
    clear();
    swap(other);
  }
  return *this;
}
template <typename T>
List<T>::List(const std::initializer_list<T> &items) : List() {
  for (const T &value : items) {
    push_back(value);
  }
}

template <typename T> T &List<T>::front() {
  return head->data;
} // front(): возвращает ссылку на данные первого элемента списка.

template <typename T> const T &List<T>::front() const { return head->data; }

// front(): возвращает ссылку на данные первого элемента списка если ссылка
// константная.

template <typename T> T &List<T>::back() {
  return tail->data;
} // back(): возвращает ссылку на данные последнего элемента списка.

template <typename T> const T &List<T>::back() const { return tail->data; }

template <typename T> typename List<T>::Iterator List<T>::begin() {
  return Iterator(head);
} // begin(): возвращает итератор на первый элемент списка.
template <typename T> typename List<T>::Iterator List<T>::end() {
  return Iterator(nullptr);
} // end(): возвращает итератор, указывающий на элемент, следующий за последним
  // элементом списка т.е nullptr

template <typename T> bool List<T>::empty() const {
  return length == 0;
} // empty() const: возвращает true, если список пуст (т.е. его длина равна 0),
  // иначе возвращает false.

template <typename T> size_t List<T>::size() const {
  return length;
} // size() const: возвращает количество элементов в списке.

template <typename T> size_t List<T>::max_size() const {
  size_t node_size = sizeof(Node);

  size_t max_size_t = static_cast<size_t>(-1);

  size_t max_nodes = max_size_t / node_size;

  return max_nodes;
} // max_size() const: возвращает максимально возможное количество элементов в
  // списке, исходя из доступной памяти и размера узла (Node).

template <typename T> void List<T>::clear() {
  while (!empty())
    pop_front(); // pop_front используется для удаления первого элемента из
                 // списка
}
/**
 * pop_front работает по принципу
 * void List<T>::pop_front() {
 * if (head) {  // Проверка, что список не пуст
 * Node* old_head = head;  // Временный указатель на текущий первый элемент
 * head = head->next;  // Перемещаем голову на следующий элемент
 * if (head)
 * head->prev = nullptr;  // Удаляем ссылку на предыдущий элемент у новой
 * головы
 * else tail = nullptr;  // Если список стал пустым, обновляем хвост delete
 * old_head;  // Удаляем первый элемент
 * --length;  // Уменьшаем длину списка
 */

template <typename T> // добавляет элемент в список
typename List<T>::Iterator List<T>::insert(Iterator pos, const T &value) {
  Node *current = pos.node_;
  Node *new_node = new Node(value);
  if (current) {
    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev) {
      current->prev->next = new_node;
    } else {
      head = new_node;
    }
    current->prev = new_node;
  } else {
    push_back(value);
    return Iterator(tail);
  }
  ++length;
  return Iterator(new_node);
}

template <typename T> void List<T>::erase(Iterator pos) {
  Node *current = pos.node_;
  if (current) {
    if (current->prev)
      current->prev->next = current->next;
    if (current->next)
      current->next->prev = current->prev;
    if (current == head)
      head = current->next;
    if (current == tail)
      tail = current->prev;
    delete current;
    --length;
  }
}

template <typename T>
void List<T>::push_back(
    const T &value) { //  push_back добавляет новый элемент в конец списка
                      //  сохраняя структуру например:
  // при пустом списке вызвав пушбэк(1) список будет head -> [1] <- tail а
  // вызвав 2 3 и 4 будет head -> [1] <-> [2] <-> [3] <-> [4] <- tail
  Node *new_node = new Node(value);
  if (tail) {
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;

  } else {
    head = tail = new_node;
  }
  ++length;
}

// push_front добавляет новый элемент в начало списка.
template <typename T> void List<T>::push_front(const T &value) {
  Node *new_node = new Node(value);
  if (head) {
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
  } else {
    head = tail = new_node;
  }
  ++length;
}
template <typename T> void List<T>::pop_front() {
  if (!head) {
    throw std::out_of_range("pop_front() called on empty list");
  }
  Node *temp = head;
  head = head->next;
  if (!head) {
    tail = nullptr;
  } else {
    head->prev = nullptr;
  }
  delete temp;
  length--;
}

template <typename T> void List<T>::swap(List &other) noexcept {
  Node *temp_head = head;
  head = other.head;
  other.head = temp_head;

  Node *temp_tail = tail;
  tail = other.tail;
  other.tail = temp_tail;

  size_t temp_length = length;
  length = other.length;
  other.length = temp_length;
}

template <typename T> void List<T>::merge(List<T> &other) {
  if (this == &other)
    return;

  auto it1 = begin();
  auto it2 = other.begin();
  while (it1 != end() && it2 != other.end()) {
    if (*it2 < *it1) {
      insert(it1, *it2);
      ++it2;
    } else {
      ++it1;
    }
  }
  while (it2 != other.end()) {
    push_back(*it2);
    ++it2;
  }
  other.clear();
}

template <typename value_type>
void List<value_type>::splice(Iterator pos, List &other) {
  if (!other.empty()) {
    for (Iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, *it);
    }
    other.clear();
  }
}

/**
 * исходный список: 1 → 2 → 3 → 4 → 5
 * после вызова функции reverse
 * перевёрнутый список: 5 → 4 → 3 → 2 → 1
 */
template <typename T>
void List<T>::reverse() { // переварачивает порядок списка в обратном
                          // направлении
  if (empty()) {
    throw std::invalid_argument("empty");
  }
  Node *current = head;
  Node *temp = nullptr;

  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  temp = head;
  head = tail;
  tail = temp;
}
/**
 * удаляет все дублирующиеся последовательные элементы из двусвязного списка.
 * если два или более соседних элемента имеют одинаковое значение, оставляется
 * только один из этих элементов
 */
template <typename T> void List<T>::unique() {
  if (empty())
    throw std::invalid_argument("empty");

  Node *current = head;
  while (current && current->next) {
    if (current->data == current->next->data) {

      Node *duplicate = current->next;
      current->next = duplicate->next;

      if (duplicate->next) {
        duplicate->next->prev = current;
      } else {
        tail = current;
      }
      delete duplicate;
      --length;
    } else {
      current = current->next;
    }
  }
}
// Original list: 4 2 5 1 3
// Sorted list : 1 2 3 4 5

template <typename T> void List<T>::sort() {
  if (length < 2)
    throw std::invalid_argument("empty");

  head = merge_sort(head);
  Node *temp = head;
  while (temp->next) {
    temp = temp->next;
  }
  tail = temp;
}

// метод копирует все элементы из другого списка в текущий список.
template <typename T> void List<T>::copy(const List &other) {
  Node *current = other.head;
  while (current) {
    push_back(current->data);
    current = current->next;
  }
}

template <typename T> typename List<T>::Node *List<T>::merge_sort(Node *node) {
  if (!node || !node->next)
    return node;

  Node *middle = get_middle(node);
  Node *half = middle->next;
  middle->next = nullptr;

  return merge(merge_sort(node), merge_sort(half));
}

template <typename T>
typename List<T>::Node *List<T>::merge(Node *left, Node *right) {
  if (!left)
    return right;
  if (!right)
    return left;

  if (left->data < right->data) {
    left->next = merge(left->next, right);
    left->next->prev = left;
    left->prev = nullptr;
    return left;
  } else {
    right->next = merge(left, right->next);
    right->next->prev = right;
    right->prev = nullptr;
    return right;
  }
}

template <typename T>
typename List<T>::Node *
List<T>::get_middle(Node *node) { // находит средний узел в связном списке.
  if (!node)
    return node;

  Node *slow = node;
  Node *fast = node->next;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

template <typename T> void List<T>::pop_back() {
  if (tail) {
    Node *old_tail = tail;
    tail = tail->prev;
    if (tail)
      tail->next = nullptr;
    else
      head = nullptr;
    delete old_tail;
    --length;
  }
}

template <typename T> List<T>::~List() { clear(); }
} // namespace s21
