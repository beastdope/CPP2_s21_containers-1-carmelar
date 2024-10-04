#include "s21_map.h"
#include <limits>

namespace s21 {

template <typename Key, typename T>
Map<Key, T>::Node::Node(const value_type &data)
    : data(data), left(nullptr), right(nullptr), parent(nullptr) {}

template <typename Key, typename T>
Map<Key, T>::Map() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> init) : Map() {
  for (const auto &item : init) {
    insert(item);
  }
}

template <typename Key, typename T> Map<Key, T>::Map(const Map &other) : Map() {
  for (const auto &item : other) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&other) noexcept : Map() {
  swap(other);
}

template <typename Key, typename T> Map<Key, T>::~Map() { clear(); }

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(const Map &other) {
  if (this != &other) {
    clear();
    for (const auto &item : other) {
      insert(item);
    }
  }
  return *this;
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &&other) noexcept {
  if (this != &other) {
    clear();
    swap(other);
  }
  return *this;
}

template <typename Key, typename T> T &Map<Key, T>::at(const Key &key) {
  Node *node = find(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

template <typename Key, typename T> T &Map<Key, T>::operator[](const Key &key) {
  auto [it, inserted] = insert({key, T()});
  return it->second;
}

template <typename Key, typename T> bool Map<Key, T>::empty() const noexcept {
  return size_ == 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const noexcept {
  return size_;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const noexcept {
  return (size_type(-1) / sizeof(Node));
}

template <typename Key, typename T> void Map<Key, T>::clear() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T> void Map<Key, T>::clear(Node *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool>
Map<Key, T>::insert(const value_type &value) {
  Node *parent = nullptr;
  Node *current = root_;
  while (current) {
    parent = current;
    if (value.first < current->data.first) {
      current = current->left;
    } else if (value.first > current->data.first) {
      current = current->right;
    } else {
      return {iterator(current), false};
    }
  }

  Node *node = new Node(value);
  node->parent = parent;
  if (!parent) {
    root_ = node;
  } else if (value.first < parent->data.first) {
    parent->left = node;
  } else {
    parent->right = node;
  }
  ++size_;
  return {iterator(node), true};
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool>
Map<Key, T>::insert_or_assign(const Key &key, const T &value) {
  auto [it, inserted] = insert({key, value});
  if (!inserted) {
    it->second = value;
  }
  return {it, inserted};
}

template <typename Key, typename T> void Map<Key, T>::erase(iterator pos) {
  Node *node = pos.getNode();
  if (!node)
    return;

  if (!node->left) {
    transplant(node, node->right);
  } else if (!node->right) {
    transplant(node, node->left);
  } else {
    Node *successor = minimum(node->right);
    if (successor->parent != node) {
      transplant(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }
    transplant(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
  }
  delete node;
  --size_;
}

template <typename Key, typename T> void Map<Key, T>::swap(Map &other) {
  Node *temp_root = root_;
  root_ = other.root_;
  other.root_ = temp_root;

  size_t temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <typename Key, typename T> void Map<Key, T>::merge(Map &other) {
  for (auto it = other.begin(); it != other.end();) {
    insert(*it++);
  }
  other.clear();
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key &key) const {
  return find(key) != nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return iterator(minimum(root_));
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr);
}
template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() const {
  return iterator(minimum(root_));
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() const {
  return iterator(nullptr);
}
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::iterator::getNode() const {
  return node_;
}
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::find(const Key &key) const {
  Node *current = root_;
  while (current) {
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
void Map<Key, T>::transplant(Node *u, Node *v) {
  if (!u->parent) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v) {
    v->parent = u->parent;
  }
}

template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::minimum(Node *node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
Map<Key, T>::iterator::iterator(Node *node) : node_(node) {}

template <typename Key, typename T>
typename Map<Key, T>::value_type &Map<Key, T>::iterator::operator*() const {
  return node_->data;
}

template <typename Key, typename T>
typename Map<Key, T>::value_type *Map<Key, T>::iterator::operator->() const {
  return &(node_->data);
}
template <typename Key, typename T>
bool Map<Key, T>::iterator::operator==(const Node *node) const {
  return node_ == node;
}

template <typename Key, typename T>
bool Map<Key, T>::iterator::operator!=(const Node *node) const {
  return node_ != node;
}
template <typename Key, typename T>
typename Map<Key, T>::iterator &Map<Key, T>::iterator::operator++() {
  if (node_) {
    if (node_->right) {
      node_ = minimum(node_->right);
    } else {
      Node *parent = node_->parent;
      while (parent && node_ == parent->right) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::iterator::operator++(int) {
  iterator tmp(*this);
  ++(*this);
  return tmp;
}
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::maximum(Node *node) {
  while (node && node->right) {
    node = node->right;
  }
  return node;
}
template <typename Key, typename T>
typename Map<Key, T>::iterator &Map<Key, T>::iterator::operator--() {
  if (node_) {
    if (node_->left) {
      node_ = maximum(node_->left);
    } else {
      Node *parent = node_->parent;
      while (parent && node_ == parent->left) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::iterator::operator--(int) {
  iterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename Key, typename T>
bool Map<Key, T>::iterator::operator==(const iterator &other) const {
  return node_ == other.node_;
}
template <typename Key, typename T>
bool Map<Key, T>::iterator::operator!=(const iterator &other) const {
  return node_ != other.node_;
}

} // namespace s21
