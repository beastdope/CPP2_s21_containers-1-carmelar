#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T> class Queue {
private:
  struct Node {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue();
  Queue &operator=(Queue &&q) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(Queue &other) noexcept;

private:
  Node *head;
  Node *tail;
  size_type length;

  void copy(const Queue &other);
};

} // namespace s21

#include "s21_queue.cpp"

#endif // S21_QUEUE_H_
