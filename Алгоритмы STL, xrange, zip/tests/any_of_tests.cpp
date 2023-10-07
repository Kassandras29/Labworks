#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool is_even_1(int a) {
    return a % 2 == 0;
}

bool is_b(char b) {
    return b == 'b';
}

TEST(AnyOf, array_int_true) {
    std::array<int, 5> arr{1, 3, 4, 7, 9};
    ASSERT_TRUE(algorithms_stl::any_of(arr.begin(), arr.end(), is_even_1));
}

TEST(AnyOf, vector_int_true) {
    std::vector<int> vec{1, 3, 4, 7, 9};
    ASSERT_TRUE(algorithms_stl::any_of(vec.begin(), vec.end(), is_even_1));
}

TEST(AnyOf, list_int_true) {
    std::list<int> l{1, 3, 4, 7, 9};
    ASSERT_TRUE(algorithms_stl::any_of(l.begin(), l.end(), is_even_1));
}
TEST(AnyOf, set_char_true) {
    std::set<char> s{'e', 'd', 'c', 'b', 'a'};
    ASSERT_TRUE(algorithms_stl::any_of(s.begin(), s.end(), is_b));
}

TEST(AnyOf, array_int_false) {
    std::array<int, 5> arr{1, 3, 5, 7, 9};
    ASSERT_FALSE(algorithms_stl::any_of(arr.begin(), arr.end(), is_even_1));
}

TEST(AnyOf, vector_char_false) {
    std::vector<char> vec{'a', 'c', 'e', 'g', 'l'};
    ASSERT_FALSE(algorithms_stl::any_of(vec.begin(), vec.end(), is_b));
}

TEST(AnyOf, list_int_false) {
    std::list<int> l{1, 3, 5, 7, 9};
    ASSERT_FALSE(algorithms_stl::any_of(l.begin(), l.end(), is_even_1));
}
TEST(AnyOf, set_int_false) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_FALSE(algorithms_stl::any_of(s.begin(), s.end(), is_even_1));
}

TEST(AnyOf, vector_empty_false) {
    std::vector<char> vec;
    ASSERT_FALSE(algorithms_stl::any_of(vec.begin(), vec.end(), is_b));
}
