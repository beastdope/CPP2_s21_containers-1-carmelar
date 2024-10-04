
#include "s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T> vector<T>::vector(size_type n) : vector() {
  size_ = n;
  capacity_ = n;
  n > 0 ? arr_ = new value_type[n] : arr_ = nullptr;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &baza) : vector() {
  size_ = baza.size();
  capacity_ = baza.size();
  arr_ = new value_type[capacity_];
  std::copy(baza.begin(), baza.end(), arr_);
}

template <typename T> vector<T>::vector(const vector &v) : vector() {
  operator=(v);
}

template <typename T> vector<T>::vector(vector &&v) : vector() {
  operator=(std::move(v));
}

template <typename T> vector<T>::~vector() { delV(); }

template <typename T> vector<T> &vector<T>::operator=(const vector &v) {
  if (this != &v) {
    delV();
    size_ = v.size_;
    capacity_ = v.capacity_;
    if (size_ > 0) {
      arr_ = new value_type[capacity_];
      for (size_type i = 0; i < size_; i++) {
        arr_[i] = v.arr_[i];
      }
    }
  }
  return *this;
}

template <typename T> vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    delV();
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = v.arr_;
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(const size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Error: invalid index");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](const size_type pos) {
  return at(pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (empty()) {
    throw std::logic_error("Error: Vector is empty");
  }
  return arr_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (empty()) {
    throw std::logic_error("Error: Vector is empty");
  }
  return arr_[size_ - 1];
}

template <typename T> typename vector<T>::iterator vector<T>::data() {
  return &arr_[0];
}

template <typename T> typename vector<T>::iterator vector<T>::begin() {
  return &arr_[0];
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return &arr_[0];
}

template <typename T> typename vector<T>::iterator vector<T>::end() {
  return &arr_[size_];
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return &arr_[size_];
}

template <typename T> bool vector<T>::empty() const { return begin() == end(); }

template <typename T> typename vector<T>::size_type vector<T>::size() {
  return std::distance(begin(), end());
}

template <typename T> typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(size_type);
}

template <typename T> void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Error: out of range memory");
  }
  if (size > capacity_) {
    iterator temp = arr_;
    arr_ = new value_type[size];
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = temp[i];
    }
    delete[] temp;
    capacity_ = size;
  }
}

template <typename T> void vector<T>::resize(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Error: out of range memory");
  }
  if (size > capacity_) {
    reserve(size);
  }
  if (size > size_) {
    for (size_type i = size_; i < size; ++i) {
      arr_[i] = value_type();
    }
  }
  size_ = size;
}

template <typename T> typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T> void vector<T>::reduce() {
  capacity_ = size_;
  reserve(capacity_);
}

template <typename T> void vector<T>::clear() { size_ = 0; }

template <typename T> void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::length_error("Error: empty size");
  }
  size_ -= 1;
}

template <typename T> void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    if (capacity_ == 0) {
      reserve(1);
    } else {
      reserve(capacity_ + 2);
    }
  }
  arr_[size_] = value;
  size_++;
}

template <typename T> void vector<T>::swap(vector &other) {
  iterator temp_arr = arr_;
  size_type temp_size = size_;
  size_type temp_capacity = capacity_;

  arr_ = other.arr_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.arr_ = temp_arr;
  other.size_ = temp_size;
  other.capacity_ = temp_capacity;
}

template <typename T> void vector<T>::sort() { std::sort(begin(), end()); }
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::length_error("Error: invalid area of memory");
  }

  if (pos == end()) {
    push_back(value);
    return arr_ + size_ - 1;
  }
  size_type newPos = std::distance(begin(), pos);
  push_back(value);

  value_type temp = arr_[newPos];
  arr_[newPos] = value;
  for (size_type i = newPos + 1; i < size() - 1; i++) {
    std::swap(temp, arr_[i]);
  }
  arr_[size() - 1] = temp;
  return arr_ + newPos;
}

template <typename T> void vector<T>::erase(iterator pos) {
  if (pos < begin() || pos > end()) {
    throw std::length_error("Error: invalid area of memory");
  }
  for (size_t i = std::distance(begin(), pos); i < size() - 1; i++) {
    arr_[i] = arr_[i + 1];
  }
  size_ -= 1;
}

template <typename T> void vector<T>::delV() {
  if (arr_ != nullptr) {
    delete[] arr_;
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

} // namespace s21
