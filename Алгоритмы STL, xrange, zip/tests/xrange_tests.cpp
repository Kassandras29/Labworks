#include "lib/xrange.h"
#include <gtest/gtest.h>
#include <list>

TEST(xRange, start_end) {
    auto x = xRange(1.5, 5.5);

    std::vector<double> result;
    for (auto i : x) {
        result.push_back(i);
    }

    std::vector<double> vec = {1.5, 2.5, 3.5, 4.5};

    ASSERT_EQ(result, vec);
}

TEST(xRange, end) {
    auto x = xRange(4);

    std::vector<int> result;
    for (auto i : x) {
        result.push_back(i);
    }

    std::vector<int> vec = {0, 1, 2, 3};

    ASSERT_EQ(result, vec);
}

TEST(xRange, start_end_step) {
    auto x = xRange(1, 6, 2);

    std::vector<int> result;
    for (auto i : x) {
        result.push_back(i);
    }

    std::vector<int> vec = {1, 3, 5};

    ASSERT_EQ(result, vec);
}

TEST(xRange, a_z) {
    auto x = xRange('a', (char)((int)'z' + 1));

    std::vector<char> result;
    for (auto i : x) {
        result.push_back(i);
    }

    std::vector<char> vec = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                             's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    ASSERT_EQ(result, vec);
}
