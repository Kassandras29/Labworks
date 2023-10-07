#pragma once
#include <utility>

template<typename T1, typename T2>
class Zip {
public:

    Zip(T1 container1, T2 container2) : container1_(container1), container2_(container2) {}
    ~Zip() = default;

    Zip& operator=(const Zip& z) = default;

    class Iterator {
    public:

        Iterator(typename T1::iterator it1, typename T2::iterator it2) : it1_(it1), it2_(it2) {}
        Iterator(const Iterator& other_it) {
            it1_ = other_it.it1_;
            it2_ = other_it.it2_;
        }

        ~Iterator() = default;

        Iterator& operator=(const Iterator& other_it) {
            it1_ = other_it.it1_;
            it2_ = other_it.it2_;

            return *this;
        }

        Iterator& operator++() {
            ++it1_;
            ++it2_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            operator++();
            return temp;
        }

        bool operator==(const Iterator& rhs) {
            return (it1_ == rhs.it1_) || (it2_ == rhs.it2_);
        }

        bool operator!=(const Iterator& rhs) {
            return !operator==(rhs);
        }

        std::pair<typename T1::value_type, typename T2::value_type> operator*() {
            return {*it1_, *it2_};
        }

    private:
        typename T1::iterator it1_;
        typename T2::iterator it2_;

    };

    Iterator begin() {
        return {container1_.begin(), container2_.begin()};
    }

    Iterator end() {
        return {container1_.end(), container2_.end()};
    }

private:
    T1 container1_;
    T2 container2_;

};
