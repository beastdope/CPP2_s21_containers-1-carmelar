#include "s21_array.h"
#include <limits>

namespace s21 {

template <typename T>
array<T>::array() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
array<T>::array(std::initializer_list<value_type> const &items) : array() {
  size_ = items.size();
  capacity_ = items.size();
  arr_ = new value_type[capacity_];
  std::copy(items.begin(), items.end(), arr_);
}

template <typename T> array<T>::array(const array &a) : array() {
  size_ = a.size_;
  capacity_ = a.capacity_;
  if (size_ > 0) {
    arr_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = a.arr_[i];
    }
  }
}

template <typename T> array<T>::array(array &&a) : array() { swap(a); }

template <typename T> array<T>::~array() { delete[] arr_; }

template <typename T> array<T> &array<T>::operator=(array &&a) {
  if (this != &a) {
    delete[] arr_;
    swap(a);
  }
  return *this;
}

template <typename T> typename array<T>::reference array<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Error: invalid index");
  }
  return arr_[pos];
}

template <typename T>
typename array<T>::reference array<T>::operator[](size_type pos) {
  return at(pos);
}

template <typename T>
typename array<T>::const_reference array<T>::front() const {
  if (empty()) {
    throw std::logic_error("Error: Array is empty");
  }
  return arr_[0];
}

template <typename T>
typename array<T>::const_reference array<T>::back() const {
  if (empty()) {
    throw std::logic_error("Error: Array is empty");
  }
  return arr_[size_ - 1];
}

template <typename T> typename array<T>::iterator array<T>::data() {
  return arr_;
}

template <typename T> typename array<T>::iterator array<T>::begin() {
  return arr_;
}

template <typename T> typename array<T>::iterator array<T>::end() {
  return arr_ + size_;
}

template <typename T> bool array<T>::empty() const { return size_ == 0; }

template <typename T> typename array<T>::size_type array<T>::size() const {
  return size_;
}

template <typename T> typename array<T>::size_type array<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T> void array<T>::swap(array &other) {
  value_type *temp_arr = arr_;
  size_type temp_size = size_;
  size_type temp_capacity = capacity_;

  arr_ = other.arr_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.arr_ = temp_arr;
  other.size_ = temp_size;
  other.capacity_ = temp_capacity;
}

template <typename T> void array<T>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = value;
  }
}

} // namespace s21
