#ifndef S21_VECTOR
#define S21_VECTOR

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T> class vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &baza);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector &operator=(const vector &v);
  vector &operator=(vector &&v);

  reference at(const size_type pos);
  reference operator[](const size_type pos);

  const_reference front() const;
  const_reference back() const;

  iterator data();
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size();
  size_type max_size();

  void reserve(size_type size);
  void resize(size_type size);
  size_type capacity();

  void reduce();
  void clear();
  void pop_back();
  void push_back(const_reference value);
  void swap(vector &other);
  void sort();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);

private:
  iterator arr_;
  size_type size_;
  size_type capacity_;

  void delV();
};
} // namespace s21

#include "s21_vector.cpp"

#endif // S21_VECTOR
