#include "s21_stack.h"
namespace s21 {
template <typename T> Stack<T>::Stack() : head(nullptr), length(0) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items) : Stack() {
  for (auto it = items.end(); it != items.begin();) {
    push(*--it);
  }
}

template <typename T> Stack<T>::Stack(const Stack &s) : Stack() {
  Node *current = s.head;
  Node *prev = nullptr;
  while (current) {
    Node *new_node = new Node(current->data);
    if (!prev) {
      head = new_node;
    } else {
      prev->next = new_node;
    }
    prev = new_node;
    current = current->next;
  }
  length = s.length;
}

template <typename T> Stack<T>::Stack(Stack &&s) noexcept : Stack() {
  move_from(std::move(s));
}

template <typename T> Stack<T>::~Stack() { clear(); }

template <typename T> Stack<T> &Stack<T>::operator=(Stack &&s) noexcept {
  if (this != &s) {
    clear();
    move_from(std::move(s));
  }
  return *this;
}

template <typename T> typename Stack<T>::const_reference Stack<T>::top() const {
  if (!empty()) {
    return head->data;
  }
  throw std::out_of_range("Stack is empty");
}

template <typename T> bool Stack<T>::empty() const { return length == 0; }

template <typename T> typename Stack<T>::size_type Stack<T>::size() const {
  return length;
}

template <typename T> void Stack<T>::push(const_reference value) {
  Node *new_node = new Node(value, head);
  head = new_node;
  ++length;
}

template <typename T> void Stack<T>::pop() {
  if (!empty()) {
    Node *temp = head;
    head = head->next;
    delete temp;
    --length;
  } else {
    throw std::out_of_range("Stack is empty");
  }
}

template <typename T> void Stack<T>::swap(Stack &other) noexcept {
  Node *temp_head = head;
  head = other.head;
  other.head = temp_head;

  size_type temp_length = length;
  length = other.length;
  other.length = temp_length;
}

template <typename T> void Stack<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T> void Stack<T>::move_from(Stack &&s) {
  head = s.head;
  length = s.length;
  s.head = nullptr;
  s.length = 0;
}

} // namespace s21