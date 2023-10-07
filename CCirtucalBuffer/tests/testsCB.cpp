#include "lib/CCircularBuffer.h"
#include <gtest/gtest.h>
#include <string>

TEST(TestSuiteBuf, ClearTest) {

    CCircularBuffer<int> x(5, 0);
    x.clear();
    ASSERT_TRUE(x.size() == 0);

}

TEST(TestSuiteBuf, EqualityTest) {

    std::string s1 = "abc";
    std::string s2 = "bca";

    CCircularBuffer<std::string> x(3, s1);
    CCircularBuffer<std::string> y(3, s2);
    CCircularBuffer<std::string> z(3, s1);
    CCircularBuffer<std::string> m(4, s2);

    ASSERT_FALSE(x == y);
    ASSERT_TRUE(x == z);
    ASSERT_FALSE(z == m);

}

TEST(TestSuiteBuf, OperatorEqualTest) {

    CCircularBuffer<int> x(3, 3);
    CCircularBuffer<int> y(5, 5);

    y = x;
    y = y;

    ASSERT_TRUE(x == y);
    ASSERT_FALSE(x != y);

    CCircularBuffer<int> a(3, 3);
    CCircularBuffer<int> b(5, 5);

    a = b;
    ASSERT_TRUE(a == b);

    CCircularBuffer<int> z = a;
    ASSERT_TRUE(a == z);

}

TEST(TestSuiteBuf, SwapTest) {

    CCircularBuffer<int> x(3, 3);
    CCircularBuffer<int> y(5, 5);
    CCircularBuffer<int> x1(3, 3);
    CCircularBuffer<int> y1(5, 5);

    swap(x, y);
    ASSERT_TRUE(x == y1);
    ASSERT_TRUE(y == x1);

    x.swap(y);
    ASSERT_TRUE(x == x1);
    ASSERT_TRUE(y == y1);

}

TEST(TestSuiteBuf, SizeTest) {

    CCircularBuffer<int> x;
    CCircularBuffer<int> y(5, 1);
    CCircularBuffer<std::string> z(0, "abg");

    ASSERT_TRUE(x.size() == 0);
    ASSERT_TRUE(y.size() == 5);
    ASSERT_TRUE(z.empty());

    y = x;
    ASSERT_TRUE(y.empty());

}

TEST(TestSuiteBuf, ResizeTest) {

    CCircularBuffer<int> x (3, 2);
    x.resize(5);
    ASSERT_EQ(x.front(), 2);
    ASSERT_EQ(x.size(), 5);
    ASSERT_EQ(x.max_size(), 5);

    CCircularBuffer<char> y (10, 'a');
    y.resize(3);
    ASSERT_EQ(y.front(), 'a');
    ASSERT_EQ(y.back(), 'a');
    ASSERT_EQ(y.size(), 3);
    ASSERT_EQ(y.max_size(), 10);
}

TEST(TestSuiteBuf, PushBackTest) {
    CCircularBuffer<int> x (4, 0);

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    ASSERT_EQ(x.size(), 4);

    ASSERT_EQ(x[0], 2);
    ASSERT_EQ(x[1], 3);
    ASSERT_EQ(x[2], 4);
    ASSERT_EQ(x[3], 5);


}

TEST(TestSuiteBuf, PushPopTest) {

    CCircularBuffer<int> x (6, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    ASSERT_EQ(x.size(), 1);

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_EQ(x.size(), 4);

    ASSERT_EQ(x[0], 0);
    ASSERT_EQ(x[1], 1);
    ASSERT_EQ(x[2], 2);
    ASSERT_EQ(x[3], 3);

}

TEST(TestSuiteBuf, PushFrontTest) {

    CCircularBuffer<int> x (6, 0);

    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_front(4);
    ASSERT_EQ(x.size(), 6);


    ASSERT_EQ(x[0], 4);
    ASSERT_EQ(x[1], 3);
    ASSERT_EQ(x[2], 2);
    ASSERT_EQ(x[3], 1);
    ASSERT_EQ(x[4], 0);
    ASSERT_EQ(x[5], 0);

}

TEST(TestSuiteBuf, ReserveTest) {
    CCircularBuffer<int> x (6, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);

    x.reserve(15);

    ASSERT_EQ(x.size(), 4);
    ASSERT_EQ(x.max_size(), 15);

    ASSERT_EQ(x[0], 0);
    ASSERT_EQ(x[1], 0);
    ASSERT_EQ(x[2], 1);
    ASSERT_EQ(x[3], 2);

}

TEST(TestSuiteBuf, InsertTest1) {
    CCircularBuffer<int> x (10, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_front(5);
    x.push_front(4);
    x.push_front(3);
    x.push_front(2);
    x.push_front(1);

    x.insert(x.cbegin() + 5, 9);

    ASSERT_EQ(x[0], 1);
    ASSERT_EQ(x[1], 2);
    ASSERT_EQ(x[2], 3);
    ASSERT_EQ(x[5], 9);
    ASSERT_EQ(x[8], 0);

    ASSERT_EQ(x.size(), 9);

}

TEST(TestSuiteBuf, InsertTest2) {
    CCircularBuffer<int> x (10, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);

    x.insert(x.cend() - 2, 9);

    ASSERT_EQ(x[0], 0);
    ASSERT_EQ(x[3], 1);
    ASSERT_EQ(x[4], 9);
    ASSERT_EQ(x[5], 2);
    ASSERT_EQ(x[6], 3);

    ASSERT_EQ(x.size(), 7);

}

TEST(TestSuiteBuf, InsertTest3) {
    CCircularBuffer<int> x (10, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);

    x.insert(x.cend() - 3, 3, 9);

    ASSERT_EQ(x[0], 0);
    ASSERT_EQ(x[1], 9);
    ASSERT_EQ(x[3], 9);
    ASSERT_EQ(x[4], 0);
    ASSERT_EQ(x[5], 0);
    ASSERT_EQ(x[6], 1);

    ASSERT_EQ(x.size(), 7);
    ASSERT_EQ(x.max_size(), 10);

}

TEST(TestSuiteBuf, InsertTest4) {
    CCircularBuffer<int> x (10, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);

    x.insert(x.cend() - 3, 10, 9);

    ASSERT_EQ(x[0], 9);
    ASSERT_EQ(x[1], 9);
    ASSERT_EQ(x[2], 9);
    ASSERT_EQ(x[3], 9);
    ASSERT_EQ(x[9], 9);

    ASSERT_EQ(x.size(), 10);
    ASSERT_EQ(x.max_size(), 10);

}

TEST(TestSuiteBuf, InsertTest5) {

    CCircularBuffer<int> x (5, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    CCircularBuffer<int> y (10, 0);


    y.pop_front();
    y.pop_front();
    y.pop_front();
    y.pop_front();
    y.pop_front();
    y.pop_front();
    y.pop_front();

    y.push_back(1);

    y.insert(y.cend() - 3, x.begin() + 2, 1 + x.end());

    ASSERT_EQ(y[0], 0);
    ASSERT_EQ(y[1], 3);
    ASSERT_EQ(y[2], 4);
    ASSERT_EQ(y[3], 5);
    ASSERT_EQ(y[4], 1);
    ASSERT_EQ(y[7], 1);

    ASSERT_EQ(y.size(), 8);
    ASSERT_EQ(y.max_size(), 10);

}

TEST(TestSuiteBuf, EraseTest1) {
    CCircularBuffer<int> y (1, 3);

    ASSERT_TRUE(y.erase(y.cbegin()) == y.end());

    CCircularBuffer<int> x (5, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    x.erase(x.cbegin() + 2);

    ASSERT_EQ(x[0], 1);
    ASSERT_EQ(x[1], 2);
    ASSERT_EQ(x[2], 4);
    ASSERT_EQ(x[3], 5);

}

TEST(TestSuiteBuf, EraseTest2) {
    CCircularBuffer<int> y (3, 0);

    ASSERT_TRUE(y.erase(y.cbegin(), y.cend()) ==  y.end());

    CCircularBuffer<int> x (5, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    x.erase(x.cbegin() + 2, x.cbegin() + 4);

    ASSERT_EQ(x[0], 1);
    ASSERT_EQ(x[1], 2);
    ASSERT_EQ(x[2], 5);

    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x.max_size(), 5);

}

TEST(TestSuiteBuf, AssignTest1) {
    CCircularBuffer<int> x (5, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    CCircularBuffer<int> y (3, 0);

    y.assign(x.begin() + 1, x.begin() + 4);

    ASSERT_EQ(y[0], 2);
    ASSERT_EQ(y[1], 3);
    ASSERT_EQ(y[2], 4);
}

TEST(TestSuiteBuf, AssignTest2) {
    CCircularBuffer<int> x (5, 0);

    x.assign(6, 3);

    ASSERT_EQ(x[0], 3);
    ASSERT_EQ(x[1], 3);
    ASSERT_EQ(x[2], 3);
}

TEST(TestSuiteBuf, AlgoTest) {
    CCircularBuffer<int> x (5, 0);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    x.push_back(7);
    x.push_back(5);
    x.push_back(3);
    x.push_back(1);
    x.push_back(5);

    std::sort(x.begin(), x.end());

    ASSERT_EQ(x[0], 1);
    ASSERT_EQ(x[1], 3);
    ASSERT_EQ(x[2], 5);
    ASSERT_EQ(x[3], 5);
    ASSERT_EQ(x[4], 7);

}
