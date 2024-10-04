#ifndef S21_MAP_H
#define S21_MAP_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename Key, typename T> class Map {
public:
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;

  class iterator;

  Map();
  Map(std::initializer_list<value_type> init);
  Map(const Map &other);
  Map(Map &&other) noexcept;
  ~Map();

  Map &operator=(const Map &other);
  Map &operator=(Map &&other) noexcept;

  T &at(const Key &key);
  T &operator[](const Key &key);

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &value);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

  bool contains(const Key &key) const;

  iterator begin();
  iterator end();
  iterator begin() const;
  iterator end() const;

public:
  struct Node {
    value_type data;
    Node *left;
    Node *right;
    Node *parent;

    Node(const value_type &data);
  };

  Node *root_;
  size_type size_;

  void clear(Node *node);

  void transplant(Node *u, Node *v);
  static Node *minimum(Node *node);
  static Node *maximum(Node *node);

public:
  Node *find(const Key &key) const;
};

template <typename Key, typename T> class Map<Key, T>::iterator {
public:
  iterator(Node *node = nullptr);

  value_type &operator*() const;
  value_type *operator->() const;

  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);

  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;
  bool operator==(const Node *node) const;
  bool operator!=(const Node *node) const;
  Node *getNode() const;

private:
  Node *node_;
};

} // namespace s21
#include "s21_map.cpp"
#endif