#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iterator>
#include <limits>

namespace s21 {
template <typename T> class List {

public:
  struct Node {
    T data;
    Node *next;
    Node *prev;
    Node(const T &value) : data(value), next(nullptr), prev(nullptr){};
  };

public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

public:
  class Iterator {
  public:
    typedef std::ptrdiff_t difference_type;
    Node *node_;
    explicit Iterator(Node *node) : node_(node){};
    size_t max_size() const;
    T &operator*();
    Iterator &operator++();
    Iterator &operator--();
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;
  };

  List();
  explicit List(size_t n);
  List(std::initializer_list<T> const &items);
  List(const List &other);
  List(List &&other) noexcept;
  ~List();
  List &operator=(List &&l) noexcept;
  static size_t node_size() { return sizeof(Node); }

  T &front();
  const T &front() const;
  T &back();
  const T &back() const;

  Iterator begin();
  Iterator end();

  bool empty() const;
  size_t size() const;
  size_t max_size() const;

  void clear();
  Iterator insert(Iterator pos, const T &value);
  void erase(Iterator pos);
  void push_back(const T &value);
  void pop_back();
  void push_front(const T &value);
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void splice(Iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

public:
  Node *head;
  Node *tail;
  size_t length;

  void copy(const List &other);
  Node *merge_sort(Node *node);
  Node *merge(Node *left, Node *right);
  Node *get_middle(Node *node);
};

} // namespace s21

#include "s21_list.cpp"
#endif // S21_LIST_H_
