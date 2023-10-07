#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool is_uneven_1(int a) {
    return a % 2 == 1;
}

bool is_a(char a) {
    return a == 'a';
}

TEST(AllOf, array_int_true) {
    std::array<int, 5> arr{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::all_of(arr.begin(), arr.end(), is_uneven_1));
}

TEST(AllOf, vector_char_true) {
    std::vector<char> vec{'a', 'a', 'a', 'a', 'a'};
    ASSERT_TRUE(algorithms_stl::all_of(vec.begin(), vec.end(), is_a));
}

TEST(AllOf, list_int_true) {
    std::list<int> l{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::all_of(l.begin(), l.end(), is_uneven_1));
}

TEST(AllOf, set_int_true) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::all_of(s.begin(), s.end(), is_uneven_1));
}

TEST(AllOf, array_char_false) {
    std::array<char, 5> arr{'a', 'a', 'b', 'a', 'a'};
    ASSERT_FALSE(algorithms_stl::all_of(arr.begin(), arr.end(), is_a));
}

TEST(AllOf, vector_int_false) {
    std::vector<int> vec{1, 3, 6, 7, 9};
    ASSERT_FALSE(algorithms_stl::all_of(vec.begin(), vec.end(), is_uneven_1));
}

TEST(AllOf, list_int_false) {
    std::list<int> l{1, 3, 5, 8, 9};
    ASSERT_FALSE(algorithms_stl::all_of(l.begin(), l.end(), is_uneven_1));
}

TEST(AllOf, set_int_false) {
    std::set<int> s{2, 3, 5, 7, 9};
    ASSERT_FALSE(algorithms_stl::all_of(s.begin(), s.end(), is_uneven_1));
}

TEST(AllOf, vector_empty_true) {
    std::vector<int> vec;
    ASSERT_TRUE(algorithms_stl::all_of(vec.begin(), vec.end(), is_uneven_1));
}
