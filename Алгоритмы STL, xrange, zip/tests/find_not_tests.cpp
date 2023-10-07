#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

const int int_pattern1 = 4;
const char char_pattern1 = 'a';

TEST(FindNot, array_int) {
    std::array<int, 5> arr{1, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_not(arr.begin(), arr.end(), int_pattern1), arr.begin());
}

TEST(FindNot, vector_int) {
    std::vector<int> vec{1, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_not(vec.begin(), vec.end(), int_pattern1), vec.begin());
}

TEST(FindNot, list_int) {
    std::list<int> l{4, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_not(l.begin(), l.end(), int_pattern1), ++l.begin());
}

TEST(FindNot, set_int) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_not(s.begin(), s.end(), int_pattern1), s.begin());
}

TEST(FindNot, array_char) {
    std::array<char, 5> arr{'b', 'c', 'd', 'e', 'f'};
    ASSERT_EQ(algorithms_stl::find_not(arr.begin(), arr.end(), char_pattern1), arr.begin());
}

TEST(FindNot, vector_char) {
    std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
    ASSERT_EQ(algorithms_stl::find_not(vec.begin(), vec.end(), char_pattern1), ++vec.begin());
}

TEST(FindNot, list_char) {
    std::list<char> l{'b', 'c', 'd', 'e', 'f'};
    ASSERT_EQ(algorithms_stl::find_not(l.begin(), l.end(), char_pattern1), l.begin());
}

TEST(FindNot, set_char) {
    std::set<char> s{'a', 'a', 'a', 'a', 'a'};
    ASSERT_EQ(algorithms_stl::find_not(s.begin(), s.end(), char_pattern1), s.end());
}

TEST(FindNot, vector_empty) {
    std::vector<int> vec;
    ASSERT_EQ(algorithms_stl::find_not(vec.begin(), vec.end(), int_pattern1), vec.end());
}
