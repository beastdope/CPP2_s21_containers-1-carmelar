#include "s21_container.h"
#include <gtest/gtest.h>
#include <list>

TEST(ListTest, construct) {
  s21::List<int> list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}
TEST(ListTest, size_constructor) {
  s21::List<int> list(5);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), 5);
}
TEST(ListTest, init) {
  s21::List<int> list = {1, 2, 3};
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, copy_constructor) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2(list1);
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
}

TEST(ListTest, move_constructor) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2(std::move(list1));
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, push_back) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, push_front) {
  s21::List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 3);
}

TEST(ListTest, pop_back) {
  s21::List<int> list = {1, 2, 3};
  list.pop_back();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, pop_front) {
  s21::List<int> list = {1, 2, 3};
  list.pop_front();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 2);
}

TEST(ListTest, clear) {
  s21::List<int> list = {1, 2, 3};
  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, swap) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {4, 5};
  list1.swap(list2);
  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list2.front(), 1);
}

TEST(ListTest, merge) {
  s21::List<int> list1 = {1, 3, 5};
  s21::List<int> list2 = {2, 4, 6};
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, merge_left) {
  s21::List<int> list;
  typename s21::List<int>::Node *left = nullptr;
  typename s21::List<int>::Node *right = new typename s21::List<int>::Node(5);

  typename s21::List<int>::Node *result = list.merge(left, right);

  ASSERT_EQ(result, right);
  ASSERT_EQ(result->data, 5);
  ASSERT_EQ(result->next, nullptr);
  ASSERT_EQ(result->prev, nullptr);

  delete right;
}
TEST(ListTest, get_middle_return) {
  s21::List<int> list;
  typename s21::List<int>::Node *result = list.get_middle(nullptr);

  ASSERT_EQ(result, nullptr);
}

TEST(ListTest, pop_back_empty) {
  s21::List<int> list;

  list.push_back(1);
  list.pop_back();

  ASSERT_EQ(list.head, nullptr);
}
TEST(ListTest, reverse) {
  s21::List<int> list = {1, 2, 3};
  list.reverse();
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}
TEST(ListTest, reverse_empty) {
  s21::List<int> list;
  EXPECT_ANY_THROW(list.reverse(););
}
TEST(ListTest, unique) {
  s21::List<int> list = {1, 1, 2, 3, 3};
  list.unique();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}
TEST(ListTest, unique_empty) {
  s21::List<int> list;
  EXPECT_ANY_THROW(list.unique(););
}
TEST(ListTest, sort_empty) {
  s21::List<int> list;
  EXPECT_ANY_THROW(list.sort(););
}

TEST(ListTest, sort) {
  s21::List<int> list = {3, 1, 2};
  list.sort();
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, depointer) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, increment) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}
TEST(ListTest, decrement) {
  s21::List<int> list;

  auto it = list.end();
  --it;
  EXPECT_TRUE(it == list.end());
}

TEST(ListTest, equality) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it1 = list.begin();
  auto it2 = list.begin();
  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_FALSE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 == it2);
}

TEST(ListTest, inequality) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it1 = list.begin();
  auto it2 = list.begin();
  EXPECT_FALSE(it1 != it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
  ++it2;
  EXPECT_FALSE(it1 != it2);
}

TEST(ListTest, iteration) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListTest, max_size) {
  s21::List<int> list;
  size_t max_possible_size =
      std::numeric_limits<size_t>::max() / list.node_size();
  EXPECT_EQ(list.max_size(), max_possible_size);
}
TEST(ListTest, erase_test) {
  s21::List<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.begin();
  ++it;
  myList.erase(it);

  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);

  it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, splice_test) {
  s21::List<int> listA;
  s21::List<int> listB;

  listA.push_back(1);
  listA.push_back(2);
  listA.push_back(3);

  listB.push_back(4);
  listB.push_back(5);
  listB.push_back(6);

  auto it = listA.begin();
  ++it;

  listA.splice(it, listB);

  EXPECT_EQ(listA.size(), 6);
  EXPECT_TRUE(listB.empty());

  std::vector<int> expectedOrder = {1, 4, 5, 6, 2, 3};
  int i = 0;
  for (auto &element : listA) {
    EXPECT_EQ(element, expectedOrder[i]);
    ++i;
  }
}

TEST(ListTest, splice_2) {
  s21::List<int> listA;
  s21::List<int> listB;

  listA.push_back(1);
  listA.push_back(2);
  listA.push_back(3);

  listB.push_back(4);
  listB.push_back(5);
  listB.push_back(6);

  auto it = listA.end();

  listA.splice(it, listB);

  EXPECT_EQ(listA.size(), 6);
  EXPECT_TRUE(listB.empty());

  std::vector<int> expectedOrder = {
      1, 2, 3, 4, 5, 6,
  };
  int i = 0;
  for (auto &element : listA) {
    EXPECT_EQ(element, expectedOrder[i]);
    ++i;
  }
}

TEST(ListTest, splice_3) {
  s21::List<int> listA;
  s21::List<int> listB;

  listA.push_back(1);
  listA.push_back(2);
  listA.push_back(3);

  auto it = listA.end();

  listA.splice(it, listB);

  EXPECT_EQ(listA.size(), 3);
  EXPECT_TRUE(listB.empty());

  std::vector<int> expectedOrder = {1, 2, 3};
  int i = 0;
  for (auto &element : listA) {
    EXPECT_EQ(element, expectedOrder[i]);
    ++i;
  }
}

TEST(ListTest, splice_empty) {
  s21::List<int> listA;
  s21::List<int> listB;
  listB.push_back(4);
  listB.push_back(5);
  listB.push_back(6);
  auto it = listA.begin();
  listA.splice(it, listB);
  EXPECT_EQ(listA.size(), 3);
  EXPECT_TRUE(listB.empty());
  std::vector<int> expectedOrder = {4, 5, 6};
  int i = 0;
  for (auto &element : listA) {
    EXPECT_EQ(element, expectedOrder[i]);
    ++i;
  }
  EXPECT_EQ(listA.front(), 4);
  EXPECT_EQ(listA.back(), 6);
}
TEST(ListTest, decrement_3) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto it = list.begin();
  ++it;
  --it;
  EXPECT_EQ(*it, 1);
}
TEST(ListTest, insert_2) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  auto it = list.end();
  it = list.insert(it, 3);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(*it, 3);
}
TEST(ListTest, erase_2) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto it = list.begin();

  list.erase(it);

  it = list.begin();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 2);

  EXPECT_EQ(*it, 2);
}

TEST(ListTest, erase_last_node) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  s21::List<int>::Iterator it = list.begin();
  ++it;
  ++it;
  list.erase(it);

  ASSERT_EQ(list.size(), 2);
  ASSERT_EQ(list.front(), 1);
  ASSERT_EQ(list.back(), 2);
}
TEST(ListTest, empty_pop) {
  s21::List<int> list;

  EXPECT_THROW(list.pop_front(), std::out_of_range);
}
// проверка возврата из метода merge() при попытке объединить список с самим
// собой
TEST(ListTest, merge_self) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_NO_THROW({
    list.merge(list);
    EXPECT_EQ(list.size(), 3);
  });
}
TEST(ListTest, merge_empty) {
  s21::List<int> list;
  s21::List<int> list2;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  EXPECT_NO_THROW({
    list2.merge(list);
    EXPECT_EQ(list2.size(), 3);

    auto current = list2.begin();
    EXPECT_EQ(*current, 1);
    ++current;
    EXPECT_EQ(*current, 2);
    ++current;
    EXPECT_EQ(*current, 3);
    ++current;
    EXPECT_TRUE(current == list2.end());
  });
}
TEST(ListTest, move_assign) {
  s21::List<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  s21::List<int> list2;
  list2.push_back(4);
  list2.push_back(5);

  list1 = std::move(list2);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list1.back(), 5);

  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(list2.empty());
}

//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
// origin compare function

TEST(ListTest, constr_origin) {
  s21::List<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}
TEST(ListTest, constr_origin2) {
  s21::List<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, constr_origin3) {
  s21::List<double> s21_list(5);
  std::list<double> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, copy_origin) {
  s21::List<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};
  s21::List<char> s21_list_2 = s21_list_1;
  std::list<char> std_list_2 = std_list_1;

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
  EXPECT_EQ(std_list_1.size(), std_list_2.size());
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(ListTest, move_origin) {
  s21::List<char> s21_list_1 = {'f', 'n', 'h', 'e'};
  std::list<char> std_list_1 = {'f', 'n', 'h', 'e'};
  s21::List<char> s21_list_2 = std::move(s21_list_1);
  std::list<char> std_list_2 = std::move(std_list_1);

  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_1.empty(), std_list_1.empty());
  auto it1 = s21_list_2.begin();
  auto it2 = std_list_2.begin();
  while (it1 != s21_list_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(ListTest, insert_origin) {
  s21::List<int> s21_list_1 = {'a', 'c', 'd'};
  std::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_1.begin();
  ++it;
  s21_list_1.insert(it, 'b');
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(ListTest, erase_origin) {
  s21::List<int> s21_list_1 = {'a', 'c', 'd'};
  std::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_2.begin();
  ++it;
  s21_list_2.erase(it);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(ListTest, push_origin) {
  s21::List<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(ListTest, pop_origin) {
  s21::List<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(ListTest, merge_origin) {
  s21::List<int> s21_list_1 = {5, 6, 8};
  s21::List<int> s21_list_2 = {-6, 2, 0, 1};
  std::list<int> std_list_1 = {5, 6, 8};
  std::list<int> std_list_2 = {-6, 2, 0, 1};
  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(ListTest, unique_origin) {
  s21::List<int> s21_list{5, 15, 25, 3, 24, -3, 1};
  std::list<int> std_list{5, 15, 25, 3, 24, -3, 1};
  s21_list.unique();
  std_list.unique();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, sort_origin) {
  s21::List<int> s21_list{
      15, 5, 1, 2, -1,
  };
  std::list<int> std_list{
      15, 5, 1, 2, -1,
  };
  s21_list.sort();
  std_list.sort();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

// s21_queue tests -----------------------------------------------

TEST(QueueTest, constructor) {
  s21::Queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, queue_init) {
  s21::Queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, queue_copy) {
  s21::Queue<int> q;
  q.push(10);
  q.push(20);
  s21::Queue<int> q2(q);
  EXPECT_EQ(q2.size(), 2);
  EXPECT_EQ(q2.front(), 10);
  EXPECT_EQ(q2.back(), 20);
}

TEST(QueueTest, queue_move) {
  s21::Queue<int> q;
  q.push(30);
  q.push(40);
  s21::Queue<int> q2(std::move(q));
  EXPECT_EQ(q2.size(), 2);
  EXPECT_EQ(q2.front(), 30);
  EXPECT_EQ(q2.back(), 40);
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, queue_destr) {
  s21::Queue<int> q;
  q.push(50);
  q.push(60);
  q.~Queue();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, queue_move_assign) {
  s21::Queue<int> q;
  q.push(70);
  q.push(80);
  s21::Queue<int> q2;
  q2 = std::move(q);
  EXPECT_EQ(q2.size(), 2);
  EXPECT_EQ(q2.front(), 70);
  EXPECT_EQ(q2.back(), 80);
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, front) {
  s21::Queue<int> q;
  q.push(90);
  EXPECT_EQ(q.front(), 90);
  q.push(100);
  EXPECT_EQ(q.front(), 90);
}

TEST(QueueTest, back) {
  s21::Queue<int> q;
  q.push(110);
  EXPECT_EQ(q.back(), 110);
  q.push(120);
  EXPECT_EQ(q.back(), 120);
}

TEST(QueueTest, empty) {
  s21::Queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(130);
  EXPECT_FALSE(q.empty());
}

TEST(QueueTest, size) {
  s21::Queue<int> q;
  EXPECT_EQ(q.size(), 0);
  q.push(140);
  EXPECT_EQ(q.size(), 1);
}

TEST(QueueTest, push) {
  s21::Queue<int> q;
  q.push(150);
  EXPECT_EQ(q.back(), 150);
  q.push(160);
  EXPECT_EQ(q.back(), 160);
}

TEST(QueueTest, pop) {
  s21::Queue<int> q;
  q.push(170);
  q.push(180);
  q.pop();
  EXPECT_EQ(q.front(), 180);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, swap) {
  s21::Queue<int> q;
  s21::Queue<int> q2;
  q.push(190);
  q2.push(200);
  q.swap(q2);
  EXPECT_EQ(q.front(), 200);
  EXPECT_EQ(q2.front(), 190);
}

TEST(QueueTest, queue_self) {
  s21::Queue<int> q = {1, 2, 3};
  s21::Queue<int> empty_queue;
  q = std::move(empty_queue);
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}
TEST(QueueTest, queue_empty) {
  s21::Queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
}
TEST(QueueTest, queue_empty2) {
  s21::Queue<int> q;
  EXPECT_THROW(q.back(), std::out_of_range);
}
TEST(QueueTest, queue_empty3) {
  s21::Queue<int> q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

// s21_stack tests -----------------------------------------------

TEST(StackTest, stack_construct) {
  s21::Stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, stack_initialise) {
  s21::Stack<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, stack_copy) {
  s21::Stack<int> s1 = {1, 2, 3};
  s21::Stack<int> s2(s1);
  EXPECT_EQ(s2.size(), s1.size());
  EXPECT_EQ(s2.top(), s1.top());
}

TEST(StackTest, stack_move) {
  s21::Stack<int> s1 = {1, 2, 3};
  s21::Stack<int> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 1);
}

TEST(StackTest, stack_push) {
  s21::Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, stack_swap) {
  s21::Stack<int> s1 = {1, 2, 3};
  s21::Stack<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 4);
  EXPECT_EQ(s2.top(), 1);
}

TEST(StackTest, stack_assign) {
  s21::Stack<int> s1 = {1, 2, 3};
  s21::Stack<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 1);
}

TEST(StackTest, stack_self) {
  s21::Stack<int> s = {1, 2, 3};
  s = std::move(s);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 1);
}
TEST(StackTest, stack_top_throw) {
  s21::Stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}
TEST(StackTest, stack_pop_throw) {
  s21::Stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(MapTest, map_construct) {
  s21::Map<int, int> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, map_initialize) {
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
}

TEST(MapTest, map_copy) {
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2(m1);
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2.at(1), 10);
  EXPECT_EQ(m2.at(2), 20);
  EXPECT_EQ(m2.at(3), 30);
}

TEST(MapTest, map_move) {
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2.at(1), 10);
  EXPECT_EQ(m2.at(2), 20);
  EXPECT_EQ(m2.at(3), 30);
  EXPECT_TRUE(m1.empty());
}

TEST(MapTest, map_assign) {
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2.at(1), 10);
  EXPECT_EQ(m2.at(2), 20);
  EXPECT_EQ(m2.at(3), 30);
  EXPECT_TRUE(m1.empty());
}

TEST(MapTest, map_at) {
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, map_square) {
  s21::Map<int, int> m;
  m[1] = 10;
  m[2] = 20;
  m[3] = 30;
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
}

TEST(MapTest, map_clear) {
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, map_insert) {
  s21::Map<int, int> m;
  auto res = m.insert({1, 10});
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->second, 10);
  EXPECT_EQ(m.size(), 1);
  res = m.insert({1, 20});
  EXPECT_FALSE(res.second);
  EXPECT_EQ(m.size(), 1);
}

TEST(MapTest, map_insert_assign) {
  s21::Map<int, int> m;
  auto res = m.insert_or_assign(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->second, 10);
  EXPECT_EQ(m.size(), 1);
  res = m.insert_or_assign(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->second, 20);
  EXPECT_EQ(m.size(), 1);
}

TEST(MapTest, insert_several_words) {
  s21::Map<int, std::string> map;
  map.insert({3, "three"});
  map.insert({1, "one"});
  map.insert({4, "four"});
  map.insert({2, "two"});

  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  ++it;
  EXPECT_EQ(it->first, 4);
  EXPECT_EQ(it->second, "four");

  EXPECT_EQ(map.size(), 4);
}

TEST(MapTest, map_swap) {
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::Map<int, int> m2 = {{3, 30}, {4, 40}};
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m2.contains(1));
}

TEST(MapTest, map_merge) {
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::Map<int, int> m2 = {{3, 30}, {4, 40}};
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 4);
  EXPECT_EQ(m2.size(), 0);
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m1.contains(4));
  EXPECT_FALSE(m2.contains(3));
}

TEST(MapTest, map_contains) {
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_FALSE(m.contains(4));
}

TEST(MapTest, map_assignment) {
  s21::Map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});
  map1.insert({3, "three"});

  s21::Map<int, std::string> map2;
  map2 = map1;

  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_EQ(map2.at(2), "two");
  EXPECT_EQ(map2.at(3), "three");

  map1.erase(map1.find(2));
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2.contains(2), true);
}

TEST(MapTest, map_max_size_test) {
  s21::Map<int, std::string> map1;

  auto max_size_value = map1.max_size();

  EXPECT_GT(max_size_value,
            0); // EXPECT_GT означает что первый аргумент больше чем второй //
                // carmelar
}

TEST(MapTest, EraseTwoChildren) {
  s21::Map<int, std::string> map;
  map.insert({3, "three"});
  map.insert({1, "one"});
  auto [it, inserted] = map.insert({4, "four"});
  EXPECT_TRUE(inserted);
  map.insert({2, "two"});
  map.erase(it);
  EXPECT_FALSE(map.contains(4));
  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
}
TEST(MapTest, EraseRoot) {
  s21::Map<int, std::string> map;
  auto [it, inserted] = map.insert({3, "three"});
  EXPECT_TRUE(inserted);
  map.insert({1, "one"});
  map.insert({4, "four"});
  map.insert({2, "two"});
  map.erase(it);
  EXPECT_FALSE(map.contains(3));
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(4));
  EXPECT_TRUE(map.contains(2));
}
TEST(MapTest, map_erase_non_existent) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  s21::Map<int, std::string>::iterator it = map.end();
  map.erase(it);
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_TRUE(map.contains(3));
}

TEST(MapTest, map_increment) {
  s21::Map<int, int> map;
  map.insert({5, 50});
  map.insert({3, 30});
  map.insert({7, 70});
  map.insert({6, 60});
  map.insert({8, 80});
  auto it = map.begin();
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ((*it).first, 5);
  it++;
  EXPECT_EQ((*it).first, 6);
  --it;
  EXPECT_EQ((*it).first, 5);
  it--;
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ((*it).first, 5);
  auto it_end = map.end();
  EXPECT_NE(it, it_end);
}
TEST(MapTest, map_node_equal) {
  s21::Map<int, std::string> map;
  s21::Map<int, std::string>::iterator it = map.begin();
  s21::Map<int, std::string>::Node *nodePtr = it.getNode();

  EXPECT_TRUE(it == nodePtr);
}
TEST(MapTest, map_not_equal) {
  s21::Map<int, std::string> map;
  s21::Map<int, std::string>::iterator it = map.begin();
  s21::Map<int, std::string>::Node *nodePtr = it.getNode();
  EXPECT_FALSE(it != nodePtr);
}
TEST(MapTest, map_operator_equal) {
  s21::Map<int, std::string> map;
  map[1] = "one";
  map[2] = "two";
  s21::Map<int, std::string>::iterator it1 = map.begin();
  s21::Map<int, std::string>::iterator it2 = map.begin();
  ++it2;
  std::cout << "it1.node_: " << it1.getNode() << std::endl;
  std::cout << "it2.node_: " << it2.getNode() << std::endl;
  EXPECT_FALSE(it1 == it2);
}
TEST(MapTest, map_maximum) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({4, "four"});
  map.insert({5, "five"});
  s21::Map<int, std::string>::Node *root = map.root_;
  s21::Map<int, std::string>::Node *maxNode = map.maximum(root);
  EXPECT_NE(maxNode, nullptr);
  s21::Map<int, std::string>::Node *current = root;
  while (current && current->right) {
    current = current->right;
  }
  EXPECT_EQ(maxNode, current);
}
TEST(MapTest, erase_no_child) {
  s21::Map<int, std::string> map;
  map.insert({2, "two"});
  map.insert({1, "one"});

  s21::Map<int, std::string>::iterator it = map.find(2);
  EXPECT_NE(it, map.end());

  map.erase(it);

  EXPECT_FALSE(map.contains(2));
}
TEST(MapTest, map_erase_both) {
  s21::Map<int, int> map;
  map.insert(std::make_pair(5, 50));
  map.insert(std::make_pair(3, 30));
  map.insert(std::make_pair(7, 70));
  map.insert(std::make_pair(2, 20));
  map.insert(std::make_pair(4, 40));
  map.insert(std::make_pair(6, 60));
  map.insert(std::make_pair(8, 80));

  EXPECT_TRUE(map.contains(5));
  map.erase(map.find(5));
  EXPECT_FALSE(map.contains(5));
  EXPECT_EQ(map.size(), 6);
  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(map.contains(7));
}

// s21_vector ----------------------------------------------------------------
TEST(Vector, DataMethod) {
  s21::vector<int> vec{10, 20, 30, 40, 50};
  int *data_ptr = vec.data();
  EXPECT_EQ(data_ptr[0], 10);
  EXPECT_EQ(data_ptr[1], 20);
  EXPECT_EQ(data_ptr[2], 30);
  EXPECT_EQ(data_ptr[3], 40);
  EXPECT_EQ(data_ptr[4], 50);
}

TEST(Vector, ResizeMethod) {
  s21::vector<int> vec{10, 20, 30, 40, 50};
  vec.resize(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);

  vec.resize(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);
}

TEST(Vector, CapacityMethod) {
  s21::vector<int> vec{10, 20, 30, 40, 50};
  EXPECT_EQ(vec.capacity(), 5);
  vec.resize(10);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(Vector, ClearMethod) {
  s21::vector<int> vec{10, 20, 30, 40, 50};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}
TEST(Vector, vector_reduce) {
  s21::vector<int> vec{10, 20, 30, 40, 50};
  vec.resize(10);
  EXPECT_EQ(vec.capacity(), 10);
  vec.reduce();
  EXPECT_EQ(vec.capacity(), 10);
  vec.push_back(60);
  vec.push_back(70);
  EXPECT_GE(vec.capacity(), vec.size());
  vec.resize(5);
  vec.reduce();

  EXPECT_EQ(vec.capacity(), 5);
}
TEST(Vector, vector_reduce2) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.reserve(-15), std::length_error);
}
TEST(Vector, vector_resize2) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.resize(-15), std::length_error);
}
TEST(Vector, vector_pop_back2) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.pop_back(), std::length_error);
}
TEST(Vector, vector_push_back3) {
  s21::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_GE(vec.capacity(), vec.size());
  EXPECT_GT(vec.capacity(), 0);
}
TEST(Vector, SortMethod) {
  s21::vector<int> vec{50, 20, 30, 10, 40};
  vec.sort();
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);
  EXPECT_EQ(vec[3], 40);
  EXPECT_EQ(vec[4], 50);
}
TEST(Vector, vector_move_assign) {
  s21::vector<int> vec1{1, 2, 3, 4, 5};
  s21::vector<int> vec2;
  vec2 = std::move(vec1);

  EXPECT_EQ(vec2.size(), 5);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec2[3], 4);
  EXPECT_EQ(vec2[4], 5);

  EXPECT_TRUE(vec1.empty());
  EXPECT_EQ(vec1.size(), 0);
}
TEST(Vector, vector_at) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);
  EXPECT_EQ(vec.at(3), 4);
  EXPECT_EQ(vec.at(4), 5);

  EXPECT_THROW(vec.at(5), std::out_of_range);
  EXPECT_THROW(vec.at(100), std::out_of_range);
}
TEST(Vector, Constructor_Default) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, Constructor_Initializer_vector) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, Constructor_Parameterized) {
  s21::vector<double> s21_vector(5);
  std::vector<double> std_vector(5);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}
TEST(Vector, Constructor_Copy) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = s21_vector_1;
  std::vector<char> std_vector_2 = std_vector_1;

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  EXPECT_EQ(std_vector_1.size(), std_vector_2.size());
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(Vector, Constructor_Move) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());
  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();
  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, Modifier_Insert) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  s21_vector_1.insert(it, 'b');
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  s21_vector_1.insert(s21_vector_1.end(), '5');
  EXPECT_EQ(s21_vector_1.back(), '5');
}
TEST(Vector, Modifier_Insert2) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  EXPECT_THROW(s21_vector_1.insert(0, 'b'), std::length_error);
}

TEST(Vector, Modifier_Erase) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_2.begin();
  ++it;
  s21_vector_2.erase(it);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
}
TEST(Vector, Modifier_Erase2) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_2.begin();
  ++it;
  EXPECT_THROW(s21_vector_2.erase(0), std::length_error);
}

TEST(Vector, Modifier_Push) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.push_back(5);
  std_vector.push_back(5);
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, Modifier_Pop) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.pop_back();
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Vector, Modifier_Swap) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::vector<char> s21_vector_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_vector_1.swap(s21_vector_2);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  auto it3 = s21_vector_3.begin();
  auto it4 = s21_vector_4.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_vector_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_4.size());
  EXPECT_EQ(s21_vector_2.size(), s21_vector_3.size());
}

TEST(Vector, Throw) {
  s21::vector<int> v;
  EXPECT_THROW(v.front(), std::logic_error);
  EXPECT_THROW(v.back(), std::logic_error);
}

// s21_array.cpp
// ----------------------------------------------------------------

TEST(ArrayTest, array_construct) {
  s21::array<int> arr;
  EXPECT_TRUE(arr.empty());
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, arra_initialise) {
  s21::array<int> arr{1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, array_copy) {
  s21::array<int> arr{1, 2, 3};
  s21::array<int> copy(arr);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[2], 3);
}

TEST(ArrayTest, array_move) {
  s21::array<int> arr{1, 2, 3};
  s21::array<int> moved(std::move(arr));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[2], 3);
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, arra_element) {
  s21::array<int> arr{1, 2, 3};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 3);
}
TEST(ArrayTest, arra_element_throw) {
  s21::array<int> arr{1, 2, 3};
  EXPECT_THROW(arr.at(5), std::out_of_range);
}
TEST(ArrayTest, arra_element_throw2) {
  s21::array<int> arr;
  EXPECT_THROW(arr.front(), std::logic_error);
}
TEST(ArrayTest, arra_element_throw3) {
  s21::array<int> arr;
  EXPECT_THROW(arr.back(), std::logic_error);
}

TEST(ArrayTest, array_iterator) {
  s21::array<int> arr{1, 2, 3};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, arr.end());
}

TEST(ArrayTest, array_capacity) {
  s21::array<int> arr{1, 2, 3};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, array_modifier) {
  s21::array<int> arr{1, 2, 3};
  s21::array<int> other{4, 5, 6};
  arr.swap(other);
  EXPECT_EQ(arr[0], 4);
  EXPECT_EQ(other[0], 1);
  arr.fill(10);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[2], 10);
}

TEST(ArrayTest, array_capacity2) {
  s21::array<int> arr{1, 2, 3};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 3);
  EXPECT_GT(arr.max_size(), 0);
}
TEST(ArrayTest, array_data) {
  s21::array<int> arr{1, 2, 3, 4, 5};
  int *data_ptr = arr.data();
  EXPECT_EQ(data_ptr[0], 1);
  EXPECT_EQ(data_ptr[1], 2);
  EXPECT_EQ(data_ptr[2], 3);
  EXPECT_EQ(data_ptr[3], 4);
  EXPECT_EQ(data_ptr[4], 5);
}

TEST(ArrayTest, array_move_assign) {
  s21::array<int> arr1{1, 2, 3, 4, 5};
  s21::array<int> arr2;
  arr2 = std::move(arr1);

  EXPECT_EQ(arr2.size(), 5);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);

  EXPECT_TRUE(arr1.empty());
  EXPECT_EQ(arr1.size(), 0);
}
// s21_set.h --------------------------------

TEST(SetSuite, InitFromList) {
  std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
  s21::Set<int> testSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
  EXPECT_EQ(testSet.size(), trueSet.size());
  testSet.clear();
}

TEST(SetSuite, InitAssign) {
  std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
  s21::Set<int> testSet = s21::Set({50, 45, 1, 30, 49, 46, 55, 51, 53});
  EXPECT_EQ(testSet.size(), trueSet.size());
  testSet.clear();
}

TEST(SetSuite, InitCopy) {
  s21::Set<int> trueSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
  s21::Set<int> testSet(trueSet);

  EXPECT_EQ(testSet.size(), trueSet.size());
  EXPECT_TRUE(trueSet == testSet);

  trueSet.clear();
  testSet.clear();
}

TEST(SetSuite, InitMove) {
  s21::Set<int> moveSet({50, 45, 1, 30});
  s21::Set<int> testSet(std::move(moveSet));
  s21::Set<int> trueSet({50, 45, 1, 30});
  EXPECT_EQ(testSet.size(), trueSet.size());
  EXPECT_EQ(0u, moveSet.size());
  EXPECT_TRUE(testSet == trueSet);
  moveSet.clear();
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, Swap) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2({49, 46, 55, 51, 53});
  s21::Set<int> resSet1({49, 46, 55, 51, 53});
  s21::Set<int> resSet2({50, 45, 1, 30});
  testSet1.swap(testSet2);
  EXPECT_EQ(testSet1.size(), resSet1.size());
  EXPECT_EQ(testSet2.size(), resSet2.size());
  EXPECT_TRUE(testSet1 == resSet1);
  EXPECT_TRUE(testSet2 == resSet2);
  testSet1.clear();
  testSet2.clear();
  resSet1.clear();
  resSet2.clear();
}

TEST(SetSuite, Equal) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2({50, 45, 1, 30});
  s21::Set<int> testSet3({49, 46, 55, 51, 53});
  EXPECT_TRUE(testSet1 == testSet2);
  EXPECT_FALSE(testSet1 == testSet3);
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
}

TEST(SetSuite, Begin) {
  s21::Set<int> testSet({50, 45, 1, 30});
  std::set<int> trueSet({50, 45, 1, 30});
  EXPECT_TRUE(*testSet.begin() == *trueSet.begin());
  EXPECT_TRUE(*testSet.const_begin() == *trueSet.begin());
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, End) {
  s21::Set<int> testSet({50, 45, 1, 30});
  EXPECT_ANY_THROW(*testSet.end());
  EXPECT_ANY_THROW(*testSet.const_end());
  testSet.clear();
}

TEST(SetSuite, Empty) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_FALSE(testSet1.empty());
  EXPECT_TRUE(testSet2.empty());
  testSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Size) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  std::set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_EQ(testSet1.size(), trueSet1.size());
  EXPECT_EQ(testSet2.size(), 0u);
  testSet1.clear();
  trueSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, MaxSize) {
  // По рекомендации пиров тестировать эту функцию не стоит
  //
  // std::set<int> trueSet1;
  // s21::Set<int> testSet1;
  // EXPECT_EQ(testSet1.max_size(), trueSet1.max_size());
  // std::set<char> trueSet2;
  // s21::Set<char> testSet2;
  // EXPECT_EQ(testSet2.max_size(), trueSet2.max_size());
  // testSet1.clear();
  // testSet2.clear();
}

TEST(SetSuite, Clear) {
  s21::Set<int> testSet({50, 45, 1, 30});
  s21::Set<int> trueSet;
  EXPECT_EQ(testSet.size(), 4u);
  testSet.clear();
  EXPECT_EQ(testSet, trueSet);
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, Insert) {
  s21::Set<int> testSet1({50, 45, 1});
  s21::Set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  s21::Set<int> trueSet2({30});
  s21::Set<int> testSet3({30});
  s21::Set<int> trueSet3({30});
  EXPECT_TRUE(testSet1.insert(30).second);
  EXPECT_TRUE(testSet2.insert(30).second);
  EXPECT_FALSE(testSet3.insert(30).second);
  EXPECT_EQ(testSet1.size(), trueSet1.size());
  EXPECT_EQ(testSet2.size(), trueSet2.size());
  EXPECT_EQ(testSet3.size(), trueSet3.size());
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
  trueSet1.clear();
  trueSet2.clear();
  trueSet3.clear();
}

TEST(SetSuite, Erase) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> trueSet1({50, 45, 1});
  s21::Set<int> testSet2({30});
  s21::Set<int> trueSet2;
  s21::Set<int> testSet3({1, 2, 3});
  s21::Set<int> trueSet3({1, 2, 3});
  s21::Set<int> testSet4({2, 1});
  s21::Set<int> trueSet4({2});
  s21::Set<int> testSet5({2, 1, 3, 4, 8, 9});
  s21::Set<int> trueSet5;
  testSet1.erase(testSet1.find(30));
  testSet2.erase(testSet2.find(30));
  EXPECT_ANY_THROW(testSet3.erase(testSet3.find(30)));
  testSet4.erase(testSet4.find(1));
  testSet5.erase(testSet5.find(1));
  testSet5.erase(testSet5.find(2));
  testSet5.erase(testSet5.find(3));
  testSet5.erase(testSet5.find(4));
  testSet5.erase(testSet5.find(8));
  testSet5.erase(testSet5.find(9));
  EXPECT_ANY_THROW(testSet5.erase(testSet5.find(9)));
  EXPECT_EQ(testSet1, trueSet1);
  EXPECT_EQ(testSet2, trueSet2);
  EXPECT_EQ(testSet3, trueSet3);
  EXPECT_EQ(testSet4, trueSet4);
  EXPECT_EQ(testSet5, trueSet5);
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
  testSet4.clear();
  testSet5.clear();
  trueSet1.clear();
  trueSet2.clear();
  trueSet3.clear();
  trueSet4.clear();
  trueSet5.clear();
}

TEST(SetSuite, Erase2) {
  // delete root with 2, root with 1, root with 0
  //        normal with 2, normal with 1, leaf

  s21::Set<int> testSet1({50, 55, 45, 1, 30}); // root with 2
  s21::Set<int> trueSet1({55, 45, 1, 30});
  testSet1.erase(testSet1.find(50));
  EXPECT_EQ(testSet1, trueSet1);
  testSet1.clear();
  trueSet1.clear();

  s21::Set<int> testSet2({50, 45, 1, 30}); // root with 1
  s21::Set<int> trueSet2({45, 1, 30});
  testSet2.erase(testSet2.find(50));
  EXPECT_EQ(testSet2, trueSet2);
  testSet2.clear();
  trueSet2.clear();

  s21::Set<int> testSet3({50}); // root with 0
  s21::Set<int> trueSet3;
  testSet3.erase(testSet3.find(50));
  EXPECT_EQ(testSet3, trueSet3);
  testSet3.clear();
  trueSet3.clear();

  s21::Set<int> testSet4({50, 55, 45, 1, 30, 46}); // normal with 2
  s21::Set<int> trueSet4({50, 55, 1, 30, 46});
  testSet4.erase(testSet4.find(45));
  EXPECT_EQ(testSet4, trueSet4);
  testSet4.clear();
  trueSet4.clear();

  s21::Set<int> testSet5({50, 55, 45, 1, 30, 46}); // normal with 1
  s21::Set<int> trueSet5({50, 55, 45, 30, 46});
  testSet5.erase(testSet5.find(1));
  EXPECT_EQ(testSet5, trueSet5);
  testSet5.clear();
  trueSet5.clear();

  s21::Set<int> testSet6({50, 55, 45, 1, 30, 46}); // normal with 0
  s21::Set<int> trueSet6({50, 55, 45, 1, 46});
  testSet6.erase(testSet6.find(30));
  EXPECT_EQ(testSet6, trueSet6);
  testSet6.clear();
  trueSet6.clear();

  s21::Set<int> testSet7({50, 55, 56});
  s21::Set<int> trueSet7({50, 56});
  testSet7.erase(testSet7.find(55));
  EXPECT_EQ(testSet7, trueSet7);
  testSet7.clear();
  trueSet7.clear();

  s21::Set<int> testSet8({50, 55, 56, 54});
  s21::Set<int> trueSet8({50, 56, 54});
  testSet8.erase(testSet8.find(55));
  EXPECT_EQ(testSet8, trueSet8);
  testSet8.clear();
  trueSet8.clear();

  EXPECT_ANY_THROW(testSet6.erase(nullptr));
}

TEST(SetSuite, Find) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  std::set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_EQ(*testSet1.find(30), *trueSet1.find(30));
  EXPECT_ANY_THROW(*testSet1.find(-1));
  EXPECT_ANY_THROW(*testSet2.find(30));
  testSet1.clear();
  trueSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Contains) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_TRUE(testSet1.contains(1));
  EXPECT_TRUE(testSet1.contains(45));
  EXPECT_TRUE(testSet1.contains(50));
  EXPECT_TRUE(testSet1.contains(30));
  EXPECT_FALSE(testSet1.contains(-1));
  EXPECT_FALSE(testSet2.contains(30));
  testSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Merge) {
  s21::Set<int> testSet11({50, 45, 1, 30});
  s21::Set<int> testSet12({49, 46, 55, 51, 53});
  s21::Set<int> trueSet1({50, 45, 1, 30, 49, 46, 55, 51, 53});
  s21::Set<int> testSet21({50, 45, 1, 30});
  s21::Set<int> testSet22;
  s21::Set<int> trueSet2({50, 45, 1, 30});
  testSet11.merge(testSet12);
  testSet21.merge(testSet22);
  EXPECT_EQ(testSet11, trueSet1);
  EXPECT_EQ(testSet21, trueSet2);
  testSet11.clear();
  testSet12.clear();
  trueSet1.clear();
  testSet21.clear();
  testSet22.clear();
  trueSet2.clear();
}
TEST(SetSuite, EqualityOperatorDifferentElements) {
  s21::Set<int> set1{1, 2, 3};
  s21::Set<int> set2{1, 2, 4};

  EXPECT_FALSE(set1 == set2);
}
TEST(SetTest, InsertNoAddMakeroot) {
  s21::Set<int> set;
  auto result1 = set.insert(1);
  auto result2 = set.insert(1);

  EXPECT_TRUE(result1.second);
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(*result1.first, 1);
  EXPECT_EQ(set.size(), 1);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}