#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T> class Stack {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s) noexcept;
  ~Stack();

  Stack &operator=(Stack &&s) noexcept;

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(Stack &other) noexcept;

private:
  struct Node {
    value_type data;
    Node *next;
    Node(value_type val, Node *next_node = nullptr)
        : data(val), next(next_node) {}
  };

  Node *head;
  size_type length;

  void clear();
  void move_from(Stack &&s);
};
} // namespace s21
#include "s21_stack.cpp"
#endif