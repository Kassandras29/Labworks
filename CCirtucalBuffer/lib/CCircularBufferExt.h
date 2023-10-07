#pragma once
#include "CCircularBuffer.h"

template<typename T, typename Alloc = std::allocator<T>>
class CCircularBufferExt : public CCircularBuffer<T, Alloc> {
public:
    const uint8_t kEXPANSION_COEFF = 2;

    typedef CCircularBuffer<T> Base;

    using typename Base::AllocTraits;
    using typename Base::value_type;
    using typename Base::reference;
    using typename Base::const_reference;
    using typename Base::size_type;
    using typename Base::difference_type;
    using typename Base::iterator;
    using typename Base::const_iterator;

    explicit CCircularBufferExt(size_type n) : CCircularBuffer<T>(n) {}
    CCircularBufferExt(size_type n, const value_type& t) : CCircularBuffer<T>(n, t) {}
    CCircularBufferExt() : CCircularBuffer<T>() {}
    CCircularBufferExt(const CCircularBufferExt& other_buf) : CCircularBuffer<T>(other_buf) {}
    CCircularBufferExt(const iterator& i, const iterator& j) : CCircularBuffer<T>(i, j) {}

    void push_back(value_type t) override {
        if (Base::size_ == Base::capacity_) {
            T* old_buffer_ = Base::buffer_;
            size_t old_capacity = Base::capacity_;
            Base::capacity_ = old_capacity * kEXPANSION_COEFF;
            Base::buffer_ = AllocTraits::allocate(Base::alloc_, Base::capacity_);

            size_t i = Base::head_;
            difference_type i_circle = Base::head_circle_;

            for (size_t j = 0; (i_circle * old_capacity + i) != (Base::tail_circle_ * old_capacity + Base::tail_);
            ++i, ++j) {
                AllocTraits::construct(Base::alloc_, Base::buffer_ + j, old_buffer_[i]);
                if (i == old_capacity) {
                    i = 0;
                    ++i_circle;
                }
            }

            Base::head_ = 0;
            Base::head_circle_ = 0;
            Base::tail_ = Base::size_;
            Base::tail_circle_ = 0;

            for (size_t j = 0; j < old_capacity; ++j) {
                AllocTraits::destroy(Base::alloc_, old_buffer_ + j);
            }
            AllocTraits::deallocate(Base::alloc_, old_buffer_, old_capacity);
        }

        AllocTraits::construct(Base::alloc_, Base::buffer_ + Base::tail_, t);
        ++Base::size_;
        ++Base::tail_;
        if (Base::tail_ == Base::capacity_) {
            Base::tail_ = 0;
            ++Base::tail_circle_;
        }
    }

    void push_front(value_type t) override {
        if (Base::size_ == Base::capacity_) {
            T* old_buffer_ = Base::buffer_;
            size_t old_capacity = Base::capacity_;
            Base::capacity_ = old_capacity * kEXPANSION_COEFF;
            Base::buffer_ = AllocTraits::allocate(Base::alloc_, Base::capacity_);

            size_t i = Base::head_;
            difference_type i_circle = Base::head_circle_;

            for (size_t j = 0; (i_circle * old_capacity + i) != (Base::tail_circle_ * old_capacity + Base::tail_);
                 ++i, ++j) {
                AllocTraits::construct(Base::alloc_, Base::buffer_ + j, old_buffer_[i]);
                if (i == old_capacity) {
                    i = 0;
                    ++i_circle;
                }
            }

            Base::head_ = 0;
            Base::head_circle_ = 0;
            Base::tail_ = Base::size_;
            Base::tail_circle_ = 0;

            for (size_t j = 0; j < old_capacity; ++j) {
                AllocTraits::destroy(Base::alloc_, old_buffer_ + j);
            }
            AllocTraits::deallocate(Base::alloc_, old_buffer_, old_capacity);
        }

        if (Base::head_ == 0) {
            Base::head_ = Base::capacity_ - 1;
            --Base::head_circle_;
        }
        else --Base::head_;

        AllocTraits::construct(Base::alloc_, Base::buffer_ + Base::head_, t);
        ++Base::size_;
    }

    iterator insert(const_iterator p, value_type t) override {
        return insert(p, 1, t);
    }

    iterator insert(const_iterator p, size_type n, value_type t) override {
        if (n == 0) return iterator(const_cast<T*>(p.data_ptr_), p.data_index_, Base::capacity_, p.index_circle_);

        size_t tail_with_p = (Base::tail_circle_ * Base::capacity_ + Base::tail_)
                - (p.index_circle_ * Base::capacity_ + p.data_index_);
        size_t before_p = Base::size_ - tail_with_p;

        T* old_buffer = Base::buffer_;
        size_t old_capacity = Base::capacity_;

        Base::size_ += n;
        while (Base::capacity_ < Base::size_) {
            Base::capacity_ *= kEXPANSION_COEFF;
        }
        Base::buffer_ = AllocTraits::allocate(Base::alloc_, Base::capacity_);

        size_t old_head = Base::head_;
        size_t old_head_circle = Base::head_circle_;

        Base::head_ = 0;
        Base::head_circle_ = 0;
        Base::tail_ = 0;
        Base::tail_circle_ = 0;
        Base::size_ = 0;

        for (size_t i = 0; i < before_p; ++i) {
            push_back(old_buffer[old_head]);
            ++old_head;
            if (old_head == old_capacity) {
                old_head = 0;
                ++old_head_circle;
            }
        }

        for (size_t i = 0; i < n; ++i) {
            push_back(t);
        }

        for (size_t i = 0; i < tail_with_p; ++i) {
            push_back(old_buffer[old_head]);
            ++old_head;
            if (old_head == old_capacity) {
                old_head = 0;
                ++old_head_circle;
            }
        }

        for (size_t i = 0; i < old_capacity; ++i) {
            AllocTraits::destroy(Base::alloc_, old_buffer + i);
        }
        AllocTraits::deallocate(Base::alloc_, old_buffer, old_capacity);

        return iterator(Base::buffer_ + before_p, before_p, Base::capacity_, 0);
    }

    iterator insert(const_iterator p, iterator i, iterator j) override {
        size_t n = j - i;

        if (n == 0) return iterator(const_cast<T*>(p.data_ptr_), p.data_index_, Base::capacity_, p.index_circle_);

        size_t tail_with_p = (Base::tail_circle_ * Base::capacity_ + Base::tail_)
                             - (p.index_circle_ * Base::capacity_ + p.data_index_);
        size_t before_p = Base::size_ - tail_with_p;

        T* old_buffer = Base::buffer_;
        size_t old_capacity = Base::capacity_;

        Base::size_ += n;
        while (Base::capacity_ < Base::size_) {
            Base::capacity_ *= kEXPANSION_COEFF;
        }
        Base::buffer_ = AllocTraits::allocate(Base::alloc_, Base::capacity_);

        size_t old_head = Base::head_;
        size_t old_head_circle = Base::head_circle_;

        Base::head_ = 0;
        Base::head_circle_ = 0;
        Base::tail_ = 0;
        Base::tail_circle_ = 0;
        Base::size_ = 0;

        for (size_t k = 0; k < before_p; ++k) {
            push_back(old_buffer[old_head]);
            ++old_head;
            if (old_head == old_capacity) {
                old_head = 0;
                ++old_head_circle;
            }
        }

        for (size_t k = 0; k < n; ++k) {
            push_back(i[k]);
        }

        for (size_t k = 0; k < tail_with_p; ++k) {
            push_back(old_buffer[old_head]);
            ++old_head;
            if (old_head == old_capacity) {
                old_head = 0;
                ++old_head_circle;
            }
        }

        for (size_t k = 0; k < old_capacity; ++k) {
            AllocTraits::destroy(Base::alloc_, old_buffer + k);
        }
        AllocTraits::deallocate(Base::alloc_, old_buffer, old_capacity);

        return iterator(Base::buffer_ + before_p, before_p, Base::capacity_, 0);
    }

};
