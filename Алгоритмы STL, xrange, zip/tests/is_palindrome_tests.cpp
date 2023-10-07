#include "lib/Algorithms_stl.h"
#include <gtest/gtest.h>
#include <list>

bool int_equality(int a, int b) {
    return a == b;
}

bool char_equality(char a, char b) {
    return a == b;
}

TEST(IsPalindrom, array_int_true) {
    std::array<int, 5> arr{1, 4, 7, 4, 1};
    ASSERT_TRUE(algorithms_stl::is_palindrome(arr.begin(), arr.begin() + arr.size() / 2, arr.rbegin(), int_equality));
}

TEST(IsPalindrom, vector_char_true) {
    std::vector<char> vec{'a', 'b', 'c', 'b', 'a'};
    ASSERT_TRUE(algorithms_stl::is_palindrome(vec.begin(), vec.begin() + vec.size() / 2, vec.rbegin(), char_equality));
}

TEST(IsPalindrom, list_int_true) {
    std::list<int> l{1, 3, 5, 3, 1};
    ASSERT_TRUE(algorithms_stl::is_palindrome(l.begin(), l.end(), l.rbegin(), int_equality));
}

TEST(IsPalindrom, array_int_false) {
    std::array<int, 5> arr{1, 4, 7, 9, 0};
    ASSERT_FALSE(algorithms_stl::is_palindrome(arr.begin(), arr.begin() + arr.size() / 2, arr.rbegin(), int_equality));
}

TEST(IsPalindrom, vector_int_false) {
    std::vector<int> vec{1, 5, 5, 3, 1};
    ASSERT_FALSE(algorithms_stl::is_palindrome(vec.begin(), vec.begin() + vec.size() / 2, vec.rbegin(), int_equality));
}

TEST(IsPalindrom, list_char_false) {
    std::list<char> l{'a', 'a', 'a', 'c', 'a'};
    ASSERT_FALSE(algorithms_stl::is_palindrome(l.begin(), l.end(), l.rbegin(), char_equality));
}

TEST(IsPalindrom, set_int_false) {
    std::set<int> s{1, 5, 5, 5, 1};
    ASSERT_FALSE(algorithms_stl::is_palindrome(s.begin(), s.end(), s.rbegin(), int_equality));
}

TEST(IsPalindrom, vector_empty_true) {
    std::vector<char> vec;
    ASSERT_TRUE(algorithms_stl::is_palindrome(vec.begin(), vec.begin() + vec.size() / 2, vec.rbegin(), char_equality));
}
