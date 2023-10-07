#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool is_even_2(int a) {
    return a % 2 == 0;
}

bool is_c(char c) {
    return c == 'c';
}

TEST(NoneOf, array_int_true) {
    std::array<int, 5> arr{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::none_of(arr.begin(), arr.end(), is_even_2));
}

TEST(NoneOf, vector_int_true) {
    std::vector<int> vec{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::none_of(vec.begin(), vec.end(), is_even_2));
}

TEST(NoneOf, list_char_true) {
    std::list<char> l{'a', 'b', 'd', 'e', 'f'};
    ASSERT_TRUE(algorithms_stl::none_of(l.begin(), l.end(), is_c));
}

TEST(NoneOf, set_int_true) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::none_of(s.begin(), s.end(), is_even_2));
}

TEST(NoneOf, array_char_false) {
    std::array<char, 5> arr{'a', 'b', 'c', 'd', 'e'};
    ASSERT_FALSE(algorithms_stl::none_of(arr.begin(), arr.end(), is_c));
}

TEST(NoneOf, vector_int_false) {
    std::vector<int> vec{1, 3, 6, 7, 9};
    ASSERT_FALSE(algorithms_stl::none_of(vec.begin(), vec.end(), is_even_2));
}

TEST(NoneOf, list_int_false) {
    std::list<int> l{1, 3, 5, 8, 9};
    ASSERT_FALSE(algorithms_stl::none_of(l.begin(), l.end(), is_even_2));
}

TEST(NoneOf, set_int_false) {
    std::set<int> s{2, 3, 5, 7, 9};
    ASSERT_FALSE(algorithms_stl::none_of(s.begin(), s.end(), is_even_2));
}

TEST(NoneOf, vector_empty_true) {
    std::vector<int> vec;
    ASSERT_TRUE(algorithms_stl::none_of(vec.begin(), vec.end(), is_even_2));
}
