#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <limits>
#include <vector>
namespace s21 {
template <class T> class Set {
public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

protected:
  struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    value_type data;

    Node(const value_type data) : data(data){};
    ;
    ~Node() {
      if (left) {
        delete left;
        left = nullptr;
      }
      if (right) {
        delete right;
        right = nullptr;
      }
    }
  };

private:
  Node *root_;
  size_type nodeCount_;

public:
  template <class value_type> class SetIterator {
  private:
    Node *cur;
    Node *succes;

  public:
    SetIterator() : cur(nullptr), succes(nullptr) {}

    SetIterator(Node *node) : cur(node), succes(nullptr) {}

    SetIterator operator++() {
      if (cur->right) {
        cur = cur->right;
        while (cur->left) {
          cur = cur->left;
        }
      } else {
        succes = cur->parent;
        while (cur->parent && cur == cur->parent->right) {
          cur = succes;
          succes = succes->parent;
        }
        cur = succes;
      }
      return *this;
    }

    template <class L> bool operator!=(const L &other) const {
      return (cur != other.getCurrent());
    }

    value_type operator*() const {
      if (cur == nullptr)
        throw std::invalid_argument("Null");
      return cur->data;
    }

    Node *getCurrent() const { return cur; }
  };

  template <class value_type> class ConstSetIterator {
  private:
    Node *cur;
    Node *succes;

  public:
    ConstSetIterator(Node *node) : cur(node), succes(nullptr) {}

    ConstSetIterator operator++() {
      if (cur->right) {
        cur = cur->right;
        while (cur->left) {
          cur = cur->left;
        }
      } else {
        succes = cur->parent;
        while (cur->parent && cur == cur->parent->right) {
          cur = succes;
          succes = succes->parent;
        }
        cur = succes;
      }
      return *this;
    }

    template <class L> bool operator!=(const L &other) const {
      return (cur != other.getCurrent());
    }

    value_type operator*() const {
      if (cur == nullptr)
        throw std::invalid_argument("Null pointer dereference");
      return cur->data;
    }

    Node *getCurrent() const { return cur; }
  };

  using iterator = SetIterator<T>;
  using const_iterator = ConstSetIterator<T>;

  Set() : root_(nullptr), nodeCount_(0) {}

  Set(const Set &copySet) : root_(nullptr), nodeCount_(0) {
    if (copySet.root_) {
      root_ = new Node(copySet.root_->data);
      nodeCount_++;
      copyNodes(copySet.root_, root_);
    }
  }

  Set(std::initializer_list<value_type> const &items)
      : root_(nullptr), nodeCount_(0) {
    for (auto i : items) {
      insert(i);
    }
  }

  void copyNodes(Node *source, Node *destination) {
    if (source->left) {
      destination->left = new Node(source->left->data);
      destination->left->parent = destination;
      nodeCount_++;
      copyNodes(source->left, destination->left);
    }
    if (source->right) {
      destination->right = new Node(source->right->data);
      destination->right->parent = destination;
      nodeCount_++;
      copyNodes(source->right, destination->right);
    }
  }

  Set(Set &&moveSet) : root_(moveSet.root_), nodeCount_(moveSet.nodeCount_) {
    moveSet.root_ = nullptr;
    moveSet.nodeCount_ = 0;
  }

  ~Set() {
    delete root_;
    root_ = nullptr;
    nodeCount_ = 0;
  }

  Set &operator=(Set &&s) {
    Set ptr = s;
    if (this != s) {
      clear();
      root_ = ptr.root_;
      ptr->root_ = nullptr;
    }
    return *this;
  }

  bool operator==(const Set &other) const {
    bool ret = true;
    if (size() != other.size())
      ret = false;
    else
      for (const_iterator it = const_begin(), ot = other.const_begin();
           it != const_end() && ot != other.const_end() && ret;) {
        if (*it != *ot)
          ret = false;
        ++it;
        ++ot;
      }
    return ret;
  }

  iterator begin() {
    Node *cur = root_;
    if (cur)
      while (cur->left) {
        cur = cur->left;
      }
    return cur;
  }

  const_iterator const_begin() const {
    Node *cur = root_;
    if (cur)
      while (cur->left) {
        cur = cur->left;
      }
    return cur;
  }

  iterator end() const {
    Node *cur = root_;
    if (cur) {
      while (cur->right) {
        cur = cur->right;
      }
      cur = cur->right;
    }
    return cur;
  }

  const_iterator const_end() const {
    Node *cur = root_;
    if (cur) {
      while (cur->right) {
        cur = cur->right;
      }
      cur = cur->right;
    }
    return cur;
  }

  bool empty() const { return (nodeCount_ == 0); }

  size_type size() const { return nodeCount_; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() {
    delete root_;
    root_ = nullptr;
    nodeCount_ = 0;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    Node *newNode = new Node(value);
    if (root_ == nullptr) {
      root_ = newNode;
      nodeCount_++;
      return std::make_pair(iterator(newNode), true);
    }

    Node *cur = root_;
    while (true) {
      if (value < cur->data) {
        if (cur->left == nullptr) {
          cur->left = newNode;
          newNode->parent = cur;
          nodeCount_++;
          return std::make_pair(iterator(newNode), true);
        } else {
          cur = cur->left;
        }
      } else if (value > cur->data) {
        if (cur->right == nullptr) {
          cur->right = newNode;
          newNode->parent = cur;
          nodeCount_++;
          return std::make_pair(iterator(newNode), true);
        } else {
          cur = cur->right;
        }
      } else {
        delete newNode;
        return std::make_pair(iterator(cur), false);
      }
    }
  }

  void erase(iterator pos) {
    if (pos.getCurrent() == nullptr)
      throw std::out_of_range("Can't erase: key not found");
    if (pos.getCurrent()->left && pos.getCurrent()->right) { // both
      erase_two(pos);
    } else if (pos.getCurrent()->left || pos.getCurrent()->right) { // only one
      erase_one(pos);
    } else { // no children
      erase_no(pos);
    }
    --nodeCount_;
  }

  void erase_two(iterator pos) {
    Node *largest = pos.getCurrent()->left;
    while (largest->right)
      largest = largest->right;
    pos.getCurrent()->data = largest->data;
    if (largest->parent->parent) {
      if (largest->parent->right == largest)
        largest->parent->right = nullptr;
      else if (largest->parent->left == largest)
        largest->parent->left = nullptr;
    } else {
      root_->data = largest->data;
      root_->left = largest->left;
      if (largest->left) {
        largest->left->parent = root_;
        largest->left = nullptr;
      }
    }
    delete largest;
    largest = nullptr;
  }

  void erase_one(iterator pos) {
    Node *parent = pos.getCurrent()->parent;
    Node *child = (pos.getCurrent()->left) ? pos.getCurrent()->left
                                           : pos.getCurrent()->right;
    if (parent) {
      if (parent->left == pos.getCurrent())
        parent->left = child;
      else if (parent->right == pos.getCurrent())
        parent->right = child;
      child->parent = parent;
      pos.getCurrent()->left = nullptr;
      pos.getCurrent()->right = nullptr;
      delete pos.getCurrent();
    } else {
      root_->left = nullptr;
      root_->right = nullptr;
      delete root_;
      root_ = child;
      root_->parent = nullptr;
    }
  }

  void erase_no(iterator pos) {
    Node *parent = pos.getCurrent()->parent;
    if (parent) {
      if (parent->left == pos.getCurrent()) {
        delete pos.getCurrent();
        parent->left = nullptr;
      } else if (parent->right == pos.getCurrent()) {
        delete pos.getCurrent();
        parent->right = nullptr;
      }
    } else {
      delete root_;
      root_ = nullptr;
    }
  }

  void swap(Set &other) {
    Node *temp = this->root_;
    this->root_ = other.root_;
    other.root_ = temp;
    int othNodes = other.nodeCount_;
    other.nodeCount_ = nodeCount_;
    nodeCount_ = othNodes;
  }

  void merge(Set &other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(it.getCurrent()->data);
    }
  }

  iterator find(const value_type &key) {
    iterator ret = end();
    for (iterator it = begin(); it != end(); ++it) {
      if (*it == key) {
        ret = it;
        break;
      }
    }
    if (ret.getCurrent() == nullptr)
      throw std::out_of_range("Can't find key");
    return ret;
  }

  bool contains(const value_type &key) {
    bool ret = false;
    for (iterator it = begin(); it != end(); ++it) {
      if (*it == key) {
        ret = true;
        break;
      }
    }
    return ret;
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    (
        [&] {
          for (iterator iter = args.begin(); iter != args.end(); ++iter) {
            bool ret = insert(*iter).second;
            result.push_back(std::make_pair(iter, ret));
          }
        }(),
        ...);
    return result;
  }
};
} // namespace s21

#endif