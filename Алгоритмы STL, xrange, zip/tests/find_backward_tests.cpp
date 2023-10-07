#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

const int int_pattern2 = 4;
const char char_pattern2 = 'a';

TEST(FindBackward, array_int) {
    std::array<int, 5> arr{1, 3, 5, 7, 4};
    ASSERT_EQ(algorithms_stl::find_backward(arr.rbegin(), arr.rend(), int_pattern2), arr.rbegin());
}

TEST(FindBackward, vector_int) {
    std::vector<int> vec{1, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_backward(vec.rbegin(), vec.rend(), int_pattern2), vec.rend());
}

TEST(FindBackward, list_int) {
    std::list<int> l{1, 3, 5, 7, 4};
    ASSERT_EQ(algorithms_stl::find_backward(l.rbegin(), l.rend(), int_pattern2), l.rbegin());
}

TEST(FindBackward, set_int) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_EQ(algorithms_stl::find_backward(s.rbegin(), s.rend(), int_pattern2), s.rend());
}

TEST(FindBackward, array_char) {
    std::array<char, 5> arr{'e', 'd', 'c', 'b', 'a'};
    ASSERT_EQ(algorithms_stl::find_backward(arr.rbegin(), arr.rend(), char_pattern2), arr.rbegin());
}

TEST(FindBackward, vector_char) {
    std::vector<char> vec{'b', 'c', 'd', 'e', 'f'};
    ASSERT_EQ(algorithms_stl::find_backward(vec.rbegin(), vec.rend(), char_pattern2), vec.rend());
}

TEST(FindBackward, list_char) {
    std::list<char> l{'a', 'b', 'a', 'b', 'a'};
    ASSERT_EQ(algorithms_stl::find_backward(l.rbegin(), l.rend(), char_pattern2), l.rbegin());
}

TEST(FindBackward, set_char) {
    std::set<char> s{'b', 'c', 'e', 'f', 'k'};
    ASSERT_EQ(algorithms_stl::find_backward(s.rbegin(), s.rend(), char_pattern2), s.rend());
}

TEST(FindBackward, vector_empty) {
    std::vector<int> vec;
    ASSERT_EQ(algorithms_stl::find_backward(vec.rbegin(), vec.rend(), int_pattern2), vec.rend());
}
