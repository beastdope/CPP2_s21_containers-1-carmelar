#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T> class array {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array &operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

private:
  value_type *arr_;
  size_type size_;
  size_type capacity_;
};

} // namespace s21

#include "s21_array.cpp"

#endif // S21_ARRAY_H
