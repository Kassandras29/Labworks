#pragma once
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class CCircularBuffer {
public:

    template<typename U>
    class Iterator {
    public:

        friend class CCircularBuffer<T>;

        typedef std::random_access_iterator_tag iterator_category;
        typedef U value_type;
        typedef U* pointer;
        typedef U& reference;
        typedef std::make_signed_t<size_t> difference_type;

        explicit Iterator(value_type* data_ptr = nullptr, size_t data_index = 0, size_t buf_capacity = 0,
                          difference_type index_circle = 0)
                : data_ptr_(data_ptr), data_index_(data_index), index_circle_(index_circle),
                buf_capacity_(buf_capacity) {}

        Iterator(const Iterator& other_it) {
            data_ptr_ = other_it.data_ptr_;
            data_index_ = other_it.data_index_;
            index_circle_ = other_it.index_circle_;
            buf_capacity_ = other_it.buf_capacity_;
        }

        ~Iterator() = default;

        Iterator& operator=(const Iterator& other_it) {
            data_ptr_ = other_it.data_ptr_;
            data_index_ = other_it.data_index_;
            index_circle_ = other_it.index_circle_;
            buf_capacity_ = other_it.buf_capacity_;

            return *this;
        }

        reference operator*() const {
            return *data_ptr_;
        }

        pointer operator->() const {
            return data_ptr_;
        }

        Iterator& operator++() {
            ++data_index_;
            ++data_ptr_;
            if (data_index_ == buf_capacity_) {
                data_ptr_ -= buf_capacity_;
                data_index_ = 0;
                ++index_circle_;
            }

            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            operator++();

            return temp;
        }

        Iterator& operator--() {
            if (data_index_ == 0) {
                data_index_ = buf_capacity_ - 1;
                data_ptr_ += data_index_;
                --index_circle_;
            } else {
                --data_index_;
                --data_ptr_;
            }

            return *this;
        }

        Iterator operator--(int) {
            Iterator temp(*this);
            operator--();

            return temp;
        }

        Iterator& operator+=(difference_type n) {
            if (n >= 0) {
                while (n--) (*this)++;
            } else {
                while (n++) (*this)--;
            }

            return *this;
        }

        Iterator& operator-=(difference_type n) {
            (*this) += -n;
            return *this;
        }

        friend Iterator operator+(const Iterator& it, difference_type n) {
            Iterator temp = it;
            temp += n;

            return temp;
        }

        friend Iterator operator+(difference_type n, const Iterator& it) {
            Iterator temp = it;
            temp += n;

            return temp;
        }

        friend Iterator operator-(const Iterator& it, difference_type n) {
            Iterator temp = it;
            temp -= n;

            return temp;
        }

        friend difference_type operator-(const Iterator& lhs, const Iterator& rhs) {
            difference_type n1 = 0;
            difference_type n2 = 0;
            Iterator temp1 = rhs;
            Iterator temp2 = rhs;

            for (;;++temp1, ++n1, --temp2, --n2) {
                if (temp1 == lhs) return n1;
                if (temp2 == lhs) return n2;
            }
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }

        bool operator==(const Iterator& rhs) {
            return (data_index_ == rhs.data_index_) && (index_circle_ == rhs.index_circle_);
        }

        bool operator!=(const Iterator& rhs) {
            return !operator==(rhs);
        }

        bool operator<(const Iterator& rhs) {
            return (data_ptr_ - rhs.data_ptr_ < 0);
        }

        bool operator>(const Iterator& rhs) {
            return (data_ptr_ - rhs.data_ptr_ > 0);
        }

        bool operator<=(const Iterator& rhs) {
            return (data_ptr_ - rhs.data_ptr_ <= 0);
        }

        bool operator>=(const Iterator& rhs) {
            return (data_ptr_ - rhs.data_ptr_ >= 0);
        }

    public:
        value_type* data_ptr_;
        size_t data_index_;
        difference_type index_circle_;
        size_t buf_capacity_;

    };

    typedef std::allocator_traits<Alloc> AllocTraits;

    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef std::make_signed_t<size_t> difference_type;
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;

    friend class Iterator<T>;

    explicit CCircularBuffer(size_type n) : capacity_(n), alloc_(std::allocator<T>()),
    head_(0), head_circle_(0), tail_(0), tail_circle_(0), size_(0) {
        buffer_ = AllocTraits::allocate(alloc_, capacity_);
    }

    CCircularBuffer(size_type n, const value_type& t) : capacity_(n), alloc_(std::allocator<T>()),
    head_(0), head_circle_(0), tail_(0), tail_circle_(0), size_(0) {
        buffer_ = AllocTraits::allocate(alloc_, capacity_);

        for (size_t i = 0; i < capacity_; ++i) {
            AllocTraits::construct(alloc_, buffer_ + tail_, t);
            ++size_;
            ++tail_;
        }
        tail_ = 0;
        ++tail_circle_;
    }

    CCircularBuffer() : capacity_(1), alloc_(std::allocator<T>()),
    head_(0), head_circle_(0),tail_(0), tail_circle_(0), size_(0) {
        buffer_ = AllocTraits::allocate(alloc_, capacity_);
    }

    CCircularBuffer(const CCircularBuffer& other_buf) {
        head_ = other_buf.head_;
        head_circle_ = other_buf.head_circle_;
        tail_ = other_buf.tail_;
        tail_circle_ = other_buf.tail_circle_;
        size_ = other_buf.size_;
        capacity_ = other_buf.capacity_;
        buffer_ = AllocTraits::allocate(alloc_, capacity_);

        size_t i = head_;
        difference_type i_circle = head_circle_;
        for (; (i_circle * capacity_ + i) != (tail_circle_ * capacity_ + tail_); ++i) {
            AllocTraits::construct(alloc_, buffer_ + i, other_buf.buffer_[i]);
            if (i == capacity_) {
                i = 0;
                ++i_circle;
            }
        }
    }

    CCircularBuffer(const iterator& i, const iterator& j)
    : alloc_(std::allocator<T>()), head_(0), head_circle_(0), tail_(0), tail_circle_(0), size_(0) {

        capacity_ = j - i;
        buffer_ = AllocTraits::allocate(alloc_, capacity_);

        for (size_t k = head_; k < capacity_; ++k) {
            AllocTraits::construct(alloc_, buffer_ + tail_, *(i + k));
            ++size_;
            ++tail_;
        }
        tail_ %= capacity_;
        ++tail_circle_;
    }

    ~CCircularBuffer() {
        for (size_t i = 0; i < capacity_; ++i) {
            AllocTraits::destroy(alloc_, buffer_ + i);
        }
        AllocTraits::deallocate(alloc_, buffer_, capacity_);
    }

    CCircularBuffer& operator=(const CCircularBuffer& other_buf) {
        if (*this == other_buf) return *this;

        for (size_t i = 0; i < capacity_; ++i) {
            AllocTraits::destroy(alloc_, buffer_ + i);
        }
        AllocTraits::deallocate(alloc_, buffer_, capacity_);

        head_ = other_buf.head_;
        head_circle_ = other_buf.head_circle_;
        tail_ = other_buf.tail_;
        tail_circle_ = other_buf.tail_circle_;
        size_ = other_buf.size_;
        capacity_ = other_buf.capacity_;
        buffer_ = AllocTraits::allocate(alloc_, capacity_);

        size_t i = head_;
        difference_type i_circle = head_circle_;
        for (; (i_circle * capacity_ + i) != (tail_circle_ * capacity_ + tail_); ++i) {
            AllocTraits::construct(alloc_, buffer_ + i, other_buf.buffer_[i]);
            if (i == capacity_) {
                i = 0;
                ++i_circle;
            }
        }

        return *this;
    }

    reference operator[](size_type i) {
        return buffer_[(head_ + i) % capacity_];
    }

    const_reference operator[](size_type i) const {
        return buffer_[(head_ + i) % capacity_];
    }

    iterator begin() {
        return iterator(buffer_ + head_, head_, capacity_, head_circle_);
    }

    iterator end() {
        return iterator(buffer_ + tail_, tail_, capacity_, tail_circle_);
    }

    const_iterator cbegin() const {
        return const_iterator(buffer_ + head_, head_, capacity_, head_circle_);
    }

    const_iterator cend() const {
        return const_iterator(buffer_ + tail_, tail_, capacity_, tail_circle_);
    }

    void swap(CCircularBuffer& rhs) {
        CCircularBuffer<T> temp = *this;
        *this = rhs;
        rhs = temp;
    }

    friend void swap(CCircularBuffer& lhs, CCircularBuffer& rhs) {
        lhs.swap(rhs);
    }

    size_type size() {
        return size_;
    }

    size_type max_size() {
        return capacity_;
    }

    friend bool operator==(const CCircularBuffer& lhs, const CCircularBuffer& rhs) {
        if (lhs.size_ != rhs.size_) return false;

        for (size_t i = 0; i < lhs.size_; ++i) {
            if (lhs[i] != rhs[i]) return false;
        }

        return true;
    }

    friend bool operator!=(const CCircularBuffer& lhs, const CCircularBuffer& rhs) {
        return !operator==(lhs, rhs);
    }

    bool empty() {
        return size_ == 0;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        auto temp = end();
        --temp;
        return *temp;
    }

    const_reference back() const {
        auto temp = end();
        --temp;
        return *temp;
    }

    void pop_front() {
        if (size_ != 0) {
            AllocTraits::destroy(alloc_, buffer_ + head_);
            --size_;
            ++head_;
            if (head_ == capacity_) {
                head_ = 0;
                ++head_circle_;
            }
        }
    }

    void pop_back() {
        if (size_ != 0) {
            if (tail_ == 0) {
                tail_ = capacity_ - 1;
                --tail_circle_;
            }
            else --tail_;

            AllocTraits::destroy(alloc_, buffer_ + tail_);
            --size_;
        }
    }

    virtual void push_front(value_type t) {
        if (size_ == capacity_) pop_back();

        if (head_ == 0) {
            head_ = capacity_ - 1;
            --head_circle_;
        }
        else --head_;

        AllocTraits::construct(alloc_, buffer_ + head_, t);
        ++size_;
    }

    virtual void push_back(value_type t) {
        if (size_ == capacity_) pop_front();

        AllocTraits::construct(alloc_, buffer_ + tail_, t);
        ++size_;
        ++tail_;
        if (tail_ == capacity_) {
            tail_ = 0;
            ++tail_circle_;
        }
    }

    void clear() {
        for (size_t i = 0; i < capacity_; ++i) {
            AllocTraits::destroy(alloc_, buffer_ + i);
        }

        head_ = 0;
        head_circle_ = 0;
        tail_ = 0;
        tail_circle_ = 0;
        size_ = 0;
    }

    void resize(size_type n) {

        if (size_ >= n) {
            while (size_ != n) pop_back();
            return;
        }

        if (capacity_ >= n) {
            push_back(buffer_[head_]);
            return;
        }

        T* old_buffer = buffer_;
        size_t old_capacity = capacity_;

        capacity_ = n;
        buffer_ = AllocTraits::allocate(alloc_, capacity_);
        tail_ = 0;
        tail_circle_ = 0;
        size_ = 0;

        for (size_t i = 0; i < capacity_; ++i) {
            AllocTraits::construct(alloc_, buffer_ + tail_, old_buffer[(head_ + i) % old_capacity]);
            ++tail_;
            ++size_;
        }
        tail_ %= capacity_;
        ++tail_circle_;
        head_ = 0;
        head_circle_ = 0;

        for (size_t i = 0; i < old_capacity; ++i) {
            AllocTraits::destroy(alloc_, old_buffer + i);
        }
        AllocTraits::deallocate(alloc_, old_buffer, old_capacity);

    }

    void reserve(size_type n) {
        if (n > capacity_) {
            T* old_buffer = buffer_;
            size_t old_capacity = capacity_;

            capacity_ = n;
            buffer_ = AllocTraits::allocate(alloc_, capacity_);
            tail_ = 0;
            tail_circle_ = 0;

            for (size_t i = 0; i < size_; ++i) {
                AllocTraits::construct(alloc_, buffer_ + tail_, old_buffer[(head_ + i) % old_capacity]);
                ++tail_;
            }

            head_ = 0;
            head_circle_ = 0;

            for (size_t i = 0; i < old_capacity; ++i) {
                AllocTraits::destroy(alloc_, old_buffer + i);
            }
            AllocTraits::deallocate(alloc_, old_buffer, old_capacity);
        }
    }

    virtual iterator insert(const_iterator p, value_type t) {
        return insert(p, 1, t);
    }

    virtual iterator insert(const_iterator p, size_type n, value_type t) {
        if (n == 0) return iterator(const_cast<T*>(p.data_ptr_), p.data_index_, capacity_, p.index_circle_);

        if (n >= capacity_) {
            CCircularBuffer temp(capacity_, t);
            *this = temp;

            return iterator(buffer_, head_, capacity_, head_circle_);
        }

        size_t tail_with_p = (tail_circle_ * capacity_ + tail_) - (p.index_circle_ * capacity_ + p.data_index_);
        size_t before_p = size_ - tail_with_p;

        if (n + size_ > capacity_) {
            while ((size_ != capacity_ - n) || before_p != 0) {
                pop_front();
                --before_p;
            }

            while ((size_ != capacity_ - n) || tail_with_p != 1) {
                pop_back();
                --tail_with_p;
            }
        }

        size_t read = head_;

        for (size_t i = 0; i < n; ++i) {
            if (head_ == 0) {
                head_ = capacity_ - 1;
                --head_circle_;
            }
            else --head_;
        }
        size_t write = head_;

        for (size_t i = 0; i < before_p; ++i) {
            buffer_[write] = buffer_[read];

            ++write;
            write %= capacity_;
            ++read;
            read %= capacity_;
        }

        for (size_t i = 0; i < n; ++i) {
            buffer_[write] = t;

            ++write;
            write %= capacity_;
        }
        size_ += n;

        size_t index_lt = head_ + before_p;
        difference_type index_lt_circle = head_circle_;
        if (index_lt >= capacity_) {
            index_lt %= capacity_;
            ++index_lt_circle;
        }
        return iterator(buffer_ + index_lt, index_lt, capacity_, index_lt_circle);
    }

    virtual iterator insert(const_iterator p, iterator i, iterator j) {
        size_t n = j - i;

        if (n == 0) return iterator(const_cast<T*>(p.data_ptr_), p.data_index_, capacity_, p.index_circle_);

        if (n >= capacity_) {
            j -= (n - capacity_);
            CCircularBuffer temp(i, j);
            *this = temp;

            return iterator(buffer_, head_, capacity_, head_circle_);
        }

        size_t tail_with_p = (tail_circle_ * capacity_ + tail_) - (p.index_circle_ * capacity_ + p.data_index_);
        size_t before_p = size_ - tail_with_p;

        if (n + size_ > capacity_) {
            while ((size_ != capacity_ - n) || before_p != 0) {
                pop_front();
                --before_p;
            }

            while ((size_ != capacity_ - n) || tail_with_p != 1) {
                pop_back();
                --tail_with_p;
            }
        }

        size_t read = head_;

        for (size_t k = 0; k < n; ++k) {
            if (head_ == 0) {
                head_ = capacity_ - 1;
                ++head_circle_;
            }
            else --head_;
        }
        size_t write = head_;

        for (size_t k = 0; k < before_p; ++k) {
            buffer_[write] = buffer_[read];

            ++write;
            write %= capacity_;
            ++read;
            read %= capacity_;
        }

        for (size_t k = 0; k < n; ++k) {
            buffer_[write] = i[k];

            ++write;
            write %= capacity_;
        }
        size_ += n;

        size_t index_lt = head_ + before_p;
        difference_type index_lt_circle = head_circle_;
        if (index_lt >= capacity_) {
            index_lt %= capacity_;
            ++index_lt_circle;
        }
        return iterator(buffer_ + index_lt, index_lt, capacity_, index_lt_circle);
    }

    iterator insert(const_iterator p, std::initializer_list<T>& il) {
        return insert(p, il.begin(), il.end());
    }

    iterator erase(const_iterator q) {
        return erase(q, q + 1);
    }

    iterator erase(const_iterator q1, const_iterator q2) {
        T* old_buffer = buffer_;
        buffer_ = AllocTraits::allocate(alloc_, capacity_);

        size_t old_head = head_;
        size_t old_tail = tail_;
        size_t old_size = size_;

        head_ = 0;
        head_circle_ = 0;
        tail_ = 0;
        tail_circle_ = 0;

        size_t i = old_head;
        for (; i != q1.data_index_; ++i, i %= capacity_) {
            AllocTraits::construct(alloc_, buffer_ + tail_, old_buffer[i]);
            ++tail_;
            if (tail_ == capacity_) {
                tail_ = 0;
                ++tail_circle_;
            }
        }

        size_t range = 0;
        for (; i != q2.data_index_; ++i, i %= capacity_) {
            ++range;
        }

        for (; i != old_tail; ++i, i %= capacity_) {
            AllocTraits::construct(alloc_, buffer_ + tail_, old_buffer[i]);
            ++tail_;
            if (tail_ == capacity_) {
                tail_ = 0;
                ++tail_circle_;
            }
        }

        size_ = old_size - range;

        for (size_t j = 0; j < capacity_; ++j) {
            AllocTraits::destroy(alloc_, old_buffer + j);
        }
        AllocTraits::deallocate(alloc_, old_buffer, capacity_);

        if (size_ == 0) return end();
        else return iterator(const_cast<T*>(q2.data_ptr_), q2.data_index_, capacity_, q2.index_circle_);
    }

    void assign(size_type n, value_type t) {
        if (n >= capacity_) {
            CCircularBuffer temp(capacity_, t);
            *this = temp;

            return;
        }

        CCircularBuffer<T> temp(capacity_);

        for (size_t i = 0; i < n; ++i) {
            AllocTraits::construct(alloc_, temp.buffer_ + i, t);
            ++tail_;
            if (tail_ == capacity_) {
                tail_ = 0;
                ++tail_circle_;
            }
        }
        *this = temp;
    }

    void assign(iterator i, iterator j) {
        size_t n = j - i;

        if (n >= capacity_) {
            j -= (n - capacity_);

            CCircularBuffer temp(i, j);
            *this = temp;

            return;
        }

        CCircularBuffer<T> temp(capacity_);

        for (size_t k = 0; k < n; ++k) {
            AllocTraits::construct(alloc_, temp.buffer_ + k, *(i + k));
            ++tail_;
            if (tail_ == capacity_) {
                tail_ = 0;
                ++tail_circle_;
            }
        }
        *this = temp;
    }

    void assign(std::initializer_list<T>& il) {
        assign(il.begin(), il.end());
    }

protected:
    size_t head_;
    difference_type head_circle_;
    size_t tail_;
    difference_type tail_circle_;
    size_t size_;
    size_t capacity_;
    T* buffer_;
    Alloc alloc_;

};
