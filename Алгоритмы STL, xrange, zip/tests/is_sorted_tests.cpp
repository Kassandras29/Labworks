#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool int_comparator(int a, int b) {
    return (a <= b);
}

bool char_comparator(char a, char b) {
    return (a <= b);
}

TEST(IsSorted, array_int_true) {
    std::array<int, 5> arr{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::is_sorted(arr.begin(), arr.end(), int_comparator));
}

TEST(IsSorted, vector_int_true) {
    std::vector<int> vec{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::is_sorted(vec.begin(), vec.end(), int_comparator));
}

TEST(IsSorted, list_char_true) {
    std::list<char> l{'a', 'b', 'c', 'd', 'e'};
    ASSERT_TRUE(algorithms_stl::is_sorted(l.begin(), l.end(), char_comparator));
}

TEST(IsSorted, set_int_true) {
    std::set<int> s{1, 3, 5, 7, 9};
    ASSERT_TRUE(algorithms_stl::is_sorted(s.begin(), s.end(), int_comparator));
}

TEST(IsSorted, array_char_false) {
    std::array<char, 5> arr{'i', 'a', 'b', 'c', 'd'};
    ASSERT_FALSE(algorithms_stl::is_sorted(arr.begin(), arr.end(), char_comparator));
}

TEST(IsSorted, vector_int_false) {
    std::vector<int> vec{1, 3, 0, 7, 9};
    ASSERT_FALSE(algorithms_stl::is_sorted(vec.begin(), vec.end(), int_comparator));
}

TEST(IsSorted, list_int_false) {
    std::list<int> l{1, 3, 5, 2, 9};
    ASSERT_FALSE(algorithms_stl::is_sorted(l.begin(), l.end(), int_comparator));
}

TEST(IsSorted, vector_empty_true) {
    std::vector<int> vec;
    ASSERT_TRUE(algorithms_stl::is_sorted(vec.begin(), vec.end(), int_comparator));
}
