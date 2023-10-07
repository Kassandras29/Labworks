#pragma once

template<typename T>
class xRange {
public:

    const T kONE_STEP = 1;

    xRange(T start, T end) : start_(start), end_(end), step_(kONE_STEP) {};
    explicit xRange(T end) : start_(0), end_(end), step_(kONE_STEP) {};
    xRange(T start, T end, T step) : start_(start), end_(end), step_(step) {};

    ~xRange() = default;

    xRange& operator=(const xRange& r) = default;

    class Iterator {
    public:

        Iterator(T input_value, T step) : value_(input_value), step_(step) {}

        Iterator(const Iterator& other_it) {
            value_ = other_it.value_;
            step_ = other_it.step_;
        }

        ~Iterator() = default;

        Iterator& operator=(const Iterator& other_it) {
            value_ = other_it.value_;
            step_ = other_it.step_;

            return *this;
        }

        Iterator& operator++() {
            value_ += step_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            operator++();
            return temp;
        }

        bool operator==(const Iterator& rhs) {
            return value_ >= rhs.value_;
        }

        bool operator!=(const Iterator& rhs) {
            return !operator==(rhs);
        }

        T& operator*() {
            return value_;
        }

    private:
        T value_;
        T step_;

    };

    Iterator begin() {
        return {start_, step_};
    }

    Iterator end() {
        return {end_, step_};
    }

private:
    T start_;
    T end_;
    T step_;

};

