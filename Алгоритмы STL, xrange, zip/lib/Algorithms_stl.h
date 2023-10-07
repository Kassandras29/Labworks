#pragma once

namespace algorithms_stl {

    const int kONLY_ONE_ELEM = 1;

    template<typename Input_it, typename Function>
    bool all_of(Input_it start, Input_it end, Function predicate) {

        for (Input_it i = start; i != end; ++i) {
            if (!predicate(*i)) return false;
        }

        return true;
    }

    template<typename Input_it, typename Function>
    bool any_of(Input_it start, Input_it end, Function predicate) {

        for (Input_it i = start; i != end; ++i) {
            if (predicate(*i)) return true;
        }

        return false;
    }

    template<typename Input_it, typename Function>
    bool none_of(Input_it start, Input_it end, Function predicate) {

        for (Input_it i = start; i != end; ++i) {
            if (predicate(*i)) return false;
        }

        return true;
    }

    template<typename Input_it, typename Function>
    bool one_of(Input_it start, Input_it end, Function predicate) {
        int count = 0;

        for (Input_it i = start; i != end; ++i) {
            if (predicate(*i)) ++count;
        }

        if (count == kONLY_ONE_ELEM) return true;
        else return false;
    }

    template<typename Input_it, typename Function>
    bool is_sorted(Input_it start, Input_it end, Function comparator) {
        if (start == end) return true;

        Input_it next = start;
        ++next;
        while (next != end) {
            if (!comparator(*start, *next)) return false;
            ++start;
            ++next;
        }

        return true;
    }

    template<typename Input_it, typename Function>
    bool is_partitioned(Input_it start, Input_it end, Function predicate) {
        if (start == end) return true;

        while (predicate(*start) && start != end) {
            ++start;
        }
        for (Input_it i = start; i != end; ++i) {
            if (predicate(*i)) return false;
        }

        return true;
    }

    template<typename Input_it, typename Sample>
    Input_it  find_not(Input_it start, Input_it end, Sample sample) {

        for (Input_it i = start; i != end; ++i) {
            if (sample != *i) return i;
        }

        return end;
    }

    template<typename RInput_it, typename Sample>
    RInput_it find_backward(RInput_it rev_start, RInput_it rev_end, Sample sample) {

        for (; rev_start != rev_end; ++rev_start) {
            if (sample == *rev_start) return rev_start;
        }

        return rev_end;
    }

    template<typename Input_it, typename RInput_it, typename Function>
    bool is_palindrome(Input_it start, Input_it end, RInput_it rev_start, Function predicate) {

        for (; start != end; ++start, ++rev_start) {
            if (!predicate(*start, *rev_start)) return false;
        }

        return true;
    }

}
