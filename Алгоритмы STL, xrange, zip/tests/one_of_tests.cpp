#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool is_uneven_2(int a) {
    return a % 2 == 1;
}

bool is_d(char d) {
    return d == 'd';
}

TEST(OneOf, array_char_true) {
    std::array<char, 5> arr{'a', 'b', 'c', 'd', 'e'};
    ASSERT_TRUE(algorithms_stl::one_of(arr.begin(), arr.end(), is_d));
}

TEST(OneOf, vector_int_true) {
    std::vector<int> vec{1, 2, 4, 6, 8};
    ASSERT_TRUE(algorithms_stl::one_of(vec.begin(), vec.end(), is_uneven_2));
}

TEST(OneOf, list_int_true) {
    std::list<int> l{1, 2, 4, 6, 8};
    ASSERT_TRUE(algorithms_stl::one_of(l.begin(), l.end(), is_uneven_2));
}

TEST(OneOf, set_int_true) {
    std::set<int> s{1, 2, 4, 6, 8};
    ASSERT_TRUE(algorithms_stl::one_of(s.begin(), s.end(), is_uneven_2));
}

TEST(OneOf, array_int_false) {
    std::array<int, 5> arr{1, 3, 4, 6, 8};
    ASSERT_FALSE(algorithms_stl::one_of(arr.begin(), arr.end(), is_uneven_2));
}

TEST(OneOf, vector_int_false) {
    std::vector<int> vec{1, 3, 5, 6, 8};
    ASSERT_FALSE(algorithms_stl::one_of(vec.begin(), vec.end(), is_uneven_2));
}

TEST(OneOf, list_int_false) {
    std::list<int> l{1, 3, 5, 7, 8};
    ASSERT_FALSE(algorithms_stl::one_of(l.begin(), l.end(), is_uneven_2));
}

TEST(OneOf, set_char_false) {
    std::set<char> s{'a', 'b', 'c', 'e', 'f'};
    ASSERT_FALSE(algorithms_stl::one_of(s.begin(), s.end(), is_d));
}

TEST(OneOf, vector_empty_false) {
    std::vector<int> vec;
    ASSERT_FALSE(algorithms_stl::one_of(vec.begin(), vec.end(), is_uneven_2));
}
