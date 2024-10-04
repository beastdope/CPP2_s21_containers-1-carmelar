#include "s21_queue.h"

namespace s21 {

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items) : Queue() {
  for (const T &value : items) {
    push(value);
  }
}

template <typename T> Queue<T>::Queue(const Queue &q) : Queue() { copy(q); }

template <typename T> Queue<T>::Queue(Queue &&q) noexcept : Queue() { swap(q); }

template <typename T> Queue<T>::~Queue() {
  while (!empty()) {
    pop();
  }
}

template <typename T> Queue<T> &Queue<T>::operator=(Queue &&q) noexcept {
  if (this != &q) {
    while (!empty()) {
      pop();
    }
    swap(q);
  }
  return *this;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head->data;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return tail->data;
}

template <typename T> bool Queue<T>::empty() const { return length == 0; }

template <typename T> typename Queue<T>::size_type Queue<T>::size() const {
  return length;
}

template <typename T> void Queue<T>::push(const_reference value) {
  Node *new_node = new Node(value);
  if (tail) {
    tail->next = new_node;
  } else {
    head = new_node;
  }
  tail = new_node;
  ++length;
}

template <typename T> void Queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  Node *temp = head;
  head = head->next;
  if (!head) {
    tail = nullptr;
  }
  delete temp;
  --length;
}

template <typename T> void Queue<T>::swap(Queue &other) noexcept {
  Node *temp_head = head;
  Node *temp_tail = tail;
  size_t temp_length = length;

  head = other.head;
  tail = other.tail;
  length = other.length;

  other.head = temp_head;
  other.tail = temp_tail;
  other.length = temp_length;
}
template <typename T> void Queue<T>::copy(const Queue &other) {
  Node *current = other.head;
  while (current) {
    push(current->data);
    current = current->next;
  }
}

} // namespace s21
