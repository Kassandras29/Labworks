include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        algorithms_tests
        all_of_tests.cpp
        any_of_tests.cpp
        none_of_tests.cpp
        one_of_tests.cpp
        is_sorted_tests.cpp
        is_partitioned_tests.cpp
        find_not_tests.cpp
        find_backward_tests.cpp
        is_palindrome_tests.cpp
        xrange_tests.cpp
        zip_tests.cpp
)

target_link_libraries(
        algorithms_tests
        Algorithms_stl
        xrange
        zip
        GTest::gtest_main
)

target_include_directories(algorithms_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(algorithms_tests)
