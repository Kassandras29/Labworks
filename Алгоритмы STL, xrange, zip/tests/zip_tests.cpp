#include "lib/zip.h"
#include <gtest/gtest.h>
#include <list>

TEST(Zip, list_vec) {
    std::list l = {1, 2, 3, 4, 5};
    std::vector v = {'a', 'b', 'c', 'd'};

    auto z = Zip(l, v);

    std::vector<std::pair<int, char>> result;
    for(auto i : z) {
        result.push_back(i);
    }

    std::vector<std::pair<int, char>> vec = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}};

    ASSERT_EQ(result, vec);
}

TEST(Zip, arr_vec) {
    std::array a = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5};
    std::vector v = {'a', 'b', 'c', 'd', 'e', 'f'};

    auto z = Zip(a, v);

    std::vector<std::pair<double, char>> result;
    for(auto i : z) {
        result.push_back(i);
    }

    std::vector<std::pair<double, char>> vec = {{1.5, 'a'}, {2.5, 'b'}, {3.5, 'c'}, {4.5, 'd'},
                                                {5.5, 'e'}, {6.5, 'f'}};

    ASSERT_EQ(result, vec);
}
