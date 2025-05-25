#include "test_main.h"

TEST(List, Constructor) {
  s21::list<int> list;
  std::list<int> list_std;
  EXPECT_EQ(list.empty(), list_std.empty());
}

TEST(List, Constructor_Size) {
  s21::list<int> list(10);
  std::list<int> list_std(10);
  EXPECT_EQ(list.size(), list_std.size());

  s21::list<int> list1(0);
  std::list<int> list_std1(0);
  EXPECT_EQ(list1.size(), list_std1.size());
  EXPECT_EQ(list1.empty(), list_std1.empty());
}

TEST(List, Constructor_Initializer_List) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  std::list<int> list_std = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Constructor_Copy) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> l_cpy(list);
  std::list<int> list_std = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(l_cpy.front(), list_std.front());
  EXPECT_EQ(l_cpy.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  EXPECT_EQ(l_cpy.size(), list_std.size());
}

TEST(List, Constructor_Move) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> l_mv(std::move(list));
  std::list<int> list_std = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(l_mv.front(), list_std.front());
  EXPECT_EQ(l_mv.back(), list_std.back());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(l_mv.size(), list_std.size());
}

TEST(List, Operator_Copy) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> l_cpy;
  l_cpy = list;
  std::list<int> list_std = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(l_cpy.front(), list_std.front());
  EXPECT_EQ(l_cpy.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  EXPECT_EQ(l_cpy.size(), list_std.size());
  s21::list<int>::iterator it;
  std::list<int>::iterator it_std;
  it = list.end();
  it_std = list_std.end();
  EXPECT_EQ(*it, *it_std);
  s21::list<int> l_cpy1;
  l_cpy1 = list;
  it = l_cpy1.end();
  EXPECT_EQ(*it, *it_std);
}

TEST(List, Operator_Move) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> l_mv;
  l_mv = std::move(list);
  std::list<int> list_std = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(l_mv.front(), list_std.front());
  EXPECT_EQ(l_mv.back(), list_std.back());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(l_mv.size(), list_std.size());
}

TEST(List, Front) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  EXPECT_EQ(list.front(), list_std.front());
}

TEST(List, Back) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  EXPECT_EQ(list.back(), list_std.back());
}

TEST(List, Empty) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  EXPECT_EQ(list.empty(), list_std.empty());
}

TEST(List, Size) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Max_Size) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  EXPECT_EQ(list.max_size(), list_std.max_size());
}

TEST(List, Clear) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  std::list<int> list_std = {5, 4, 3, 2, 1};
  list.clear();
  list_std.clear();
  EXPECT_EQ(list.empty(), list_std.empty());
}

TEST(List, Push_Back) {
  s21::list<int> list;
  std::list<int> list_std;
  list.push_back(1);
  list_std.push_back(1);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  list.push_back(4);
  list_std.push_back(4);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Pop_Back) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  std::list<int> list_std = {1, 2, 3, 4, 5};
  list.pop_back();
  list_std.pop_back();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  list.pop_back();
  list_std.pop_back();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Push_Front) {
  s21::list<int> list;
  std::list<int> list_std;
  list.push_front(1);
  list_std.push_front(1);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  list.push_front(4);
  list_std.push_front(4);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Pop_Front) {
  s21::list<int> list = {1, 2};
  std::list<int> list_std = {1, 2};
  list.pop_front();
  list_std.pop_front();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  list.pop_front();
  list_std.pop_front();
  EXPECT_EQ(list.empty(), list_std.empty());
}

TEST(List, Swap) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> list1 = {5, 4, 3, 2, 1};
  list.swap(list1);
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 1);
  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 5);
  EXPECT_EQ(list1.size(), 5);
}

TEST(List, Reverse) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  std::list<int> list_std = {1, 2, 3, 4, 5};
  list.reverse();
  list_std.reverse();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Unique) {
  s21::list<int> list = {1, 2, 2, 2, 3, 4, 5, 5, 5};
  std::list<int> list_std = {1, 2, 2, 2, 3, 4, 5, 5, 5};
  list.unique();
  list_std.unique();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Sort) {
  s21::list<int> list = {1, 2, 3, 4, 5, 2, 4, 2, 1};
  std::list<int> list_std = {1, 2, 3, 4, 5, 2, 4, 2, 1};
  list.sort();
  list_std.sort();
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Merge) {
  s21::list<int> list = {1, 2, 3, 4};
  s21::list<int> list_m = {2, 5, 4, 3};
  std::list<int> list_std = {1, 2, 3, 4};
  std::list<int> list_std_m = {2, 5, 4, 3};
  list.sort();
  list_m.sort();
  list_std.sort();
  list_std_m.sort();
  list.merge(list_m);
  list_std.merge(list_std_m);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Insert) {
  s21::list<int> list = {1, 2, 3, 4};
  std::list<int> list_std = {1, 2, 3, 4};
  s21::list<int>::iterator it;
  std::list<int>::iterator it_std;
  it = list.begin();
  it_std = list_std.begin();
  list.insert(it, 13);
  list_std.insert(it_std, 13);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  it = list.end();
  it_std = list_std.end();
  list.insert(it, 1337);
  list_std.insert(it_std, 1337);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());

  s21::list<int> list_1;
  s21::list<int>::iterator it_1;
  std::list<int> list_std_1;
  std::list<int>::iterator it_std_1;
  it_1 = list_1.begin();
  it_std_1 = list_std_1.begin();
  list_1.insert(it_1, 5);
  list_std_1.insert(it_std_1, 5);
  EXPECT_EQ(list_1.front(), list_std_1.front());
  EXPECT_EQ(list_1.back(), list_std_1.back());
  EXPECT_EQ(list_1.size(), list_std_1.size());
  list_1.insert(it_1, 7);
  list_std_1.insert(it_std_1, 7);
  list_1.insert(it_1, 9);
  list_std_1.insert(it_std_1, 9);
  EXPECT_EQ(list_1.front(), list_std_1.front());
  EXPECT_EQ(list_1.back(), list_std_1.back());
  EXPECT_EQ(list_1.size(), list_std_1.size());

  s21::list<int> list_2 = {1, 2, 3, 4, 5, 6};
  s21::list<int>::iterator it_2 = list_2.end();
  std::list<int> list_std_2 = {1, 2, 3, 4, 5, 6};
  std::list<int>::iterator it_std_2 = list_std_2.end();
  it_2 = list_2.insert(it_2, 1337);
  it_std_2 = list_std_1.insert(it_std_2, 1337);
  EXPECT_EQ(list_2.front(), list_std_2.front());
  EXPECT_EQ(list_2.back(), list_std_2.back());
}

TEST(List, Erase) {
  s21::list<int> list = {1, 2, 3, 4, 5, 6, 7};
  s21::list<int>::iterator it;
  std::list<int> list_std = {1, 2, 3, 4, 5, 6, 7};
  std::list<int>::iterator it_std;
  list.erase(list.begin());
  list_std.erase(list_std.begin());
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  it = list.begin();
  ++it;
  it_std = list_std.begin();
  ++it_std;
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  it = list.end();
  it_std = list_std.end();
  --it;
  --it_std;
  list.erase(it);
  list_std.erase(it_std);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
  it = list.begin();
  it_std = list_std.begin();
  ++it;
  ++it_std;
  ++it;
  ++it_std;
  ++it;
  ++it_std;
  list.erase(it);
  list_std.erase(it_std);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Splice) {
  s21::list<int> list = {1};
  s21::list<int> list_1 = {2, 3, 4, 5};
  std::list<int> list_std = {1};
  std::list<int> list_std_1 = {2, 3, 4, 5};
  s21::list<int>::iterator it = list.begin();
  std::list<int>::iterator it_std = list_std.begin();
  list.splice(it, list_1);
  list_std.splice(it_std, list_std_1);
  EXPECT_EQ(list.front(), list_std.front());
  EXPECT_EQ(list.back(), list_std.back());
  EXPECT_EQ(list.size(), list_std.size());
}

TEST(List, Iterator) {
  s21::list<int> lol = {1337, 228, 123, 69};
  s21::list<int>::const_iterator itr = lol.end();
  --itr;
  EXPECT_EQ(*itr, 69);
  ++itr;
  EXPECT_EQ(*itr, 4);
  ++itr;
  EXPECT_EQ(*itr, 1337);
  --itr;
  EXPECT_EQ(*itr, 4);
  itr = itr - 2;
  EXPECT_EQ(*itr, 123);
  itr = itr + 2;
  EXPECT_EQ(*itr, 4);
  s21::list<int>::iterator itr_1 = lol.begin();
  --itr_1;
  EXPECT_EQ(*itr, 4);
}

TEST(List, Insert_Many) {
  s21::list<int> list = {1, 5, 6};
  s21::list<int>::iterator it = list.begin();
  ++it;
  list.insert_many(it, 2, 3, 4);
  it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(List, Insert_Many_Back) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::iterator it;
  list.insert_many_back(4, 5, 6);
  it = list.end();
  --it;
  EXPECT_EQ(*it, 6);
  --it;
  EXPECT_EQ(*it, 5);
  --it;
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(List, Insert_Many_Front) {
  s21::list<int> list = {4, 5, 6};
  s21::list<int>::iterator it;
  list.insert_many_front(3, 2, 1);
  it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}