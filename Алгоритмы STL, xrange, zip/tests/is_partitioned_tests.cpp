#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool is_uneven_3(int a) {
    return a % 2 == 1;
}

bool is_e(char e) {
    return e == 'e';
}

TEST(IsPartitioned, array_int_true) {
    std::array<int, 5> arr{1, 3, 7, 8, 10};
    ASSERT_TRUE(algorithms_stl::is_partitioned(arr.begin(), arr.end(), is_uneven_3));
}

TEST(IsPartitioned, vector_int_true) {
    std::vector<int> vec{1, 3, 7, 8, 10};
    ASSERT_TRUE(algorithms_stl::is_partitioned(vec.begin(), vec.end(), is_uneven_3));
}

TEST(IsPartitioned, list_char_true) {
    std::list<char> l{'a', 'b', 'c', 'd', 'f'};
    ASSERT_TRUE(algorithms_stl::is_partitioned(l.begin(), l.end(), is_e));
}

TEST(IsPartitioned, set_int_true) {
    std::set<int> s{1, 3, 7, 8, 10};
    ASSERT_TRUE(algorithms_stl::is_partitioned(s.begin(), s.end(), is_uneven_3));
}

TEST(IsPartitioned, array_int_false) {
    std::array<int, 5> arr{2, 3, 7, 8, 10};
    ASSERT_FALSE(algorithms_stl::is_partitioned(arr.begin(), arr.end(), is_uneven_3));
}

TEST(IsPartitioned, vector_char_false) {
    std::vector<char> vec{'a', 'e', 'e', 'e', 'e'};
    ASSERT_FALSE(algorithms_stl::is_partitioned(vec.begin(), vec.end(), is_e));
}

TEST(IsPartitioned, list_int_false) {
    std::list<int> l{1, 3, 7, 8, 9};
    ASSERT_FALSE(algorithms_stl::is_partitioned(l.begin(), l.end(), is_uneven_3));
}

TEST(IsPartitioned, set_int_false) {
    std::set<int> s{0, 3, 7, 8, 10};
    ASSERT_FALSE(algorithms_stl::is_partitioned(s.begin(), s.end(), is_uneven_3));
}

TEST(IsPartitioned, vector_empty_true) {
    std::vector<int> vec;
    ASSERT_TRUE(algorithms_stl::is_partitioned(vec.begin(), vec.end(), is_uneven_3));
}
