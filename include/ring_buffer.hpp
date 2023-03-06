#pragma once

#include <cstddef>
#include <memory>
#include <concepts>
#include <algorithm>
#include <array>


template<typename T, std::size_t N>

class RingBuffer {
    static_assert(N >= 2, "N must greater than 2");

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T &;
    using const_reference = const T &;

public:
    RingBuffer() : front_index(0), end_index(0) {
    }

    ~RingBuffer() = default;
    // RingBuffer(const RingBuffer &) = delete;
    // RingBuffer &operator=(const RingBuffer &) = delete;

    // RingBuffer(RingBuffer &&other) : out_(other.out_), in_(other.in_), data_(std::move(other.data_)) {}
    // RingBuffer &operator=(RingBuffer &&other)
    // {
    //     *this = std::move(other);
    // }

public:
    reference front() {
        return data_[front_index];
    }

    const_reference front() const {
        return data_[front_index];
    }

    reference back() {
        return data_[front_index];
    }

    const_reference back() const {
        return data_[front_index];
    }

public:
    [[nodiscard]] bool empty() const {
        return front()>back();
    }

    size_type size() const {
        return data_.size();
    }

public:
    void push( const value_type& value );
    void push( value_type&& value );

    template< class... Args >
    decltype(auto) emplace( Args&&... args );

    void pop();

public:



//    inline std::size_t unused() const {
//        return N - (in_ - out_);
//    }
//
//    inline bool push(std::initializer_list<T> buf) {
//        if (unused() < buf.size()) {
//            return false;
//        }
//        std::size_t off = in_ & mask_;
//        std::size_t l = std::min(buf.size(), N - off);
//        std::copy(buf.begin(), buf.begin() + l, std::begin(data_) + in_);
//        std::copy(buf.begin() + l, buf.end(), std::begin(data_));
//
//        in_ += buf.size();
//        return true;
//    }
//
//    inline bool pop(T *value) {
//        *value = data_[out_];
//        // if (is_empty())
//        // {
//        //     return false;
//        // }
//        // *value = data_[out_];
//        // out_ = (out_ + 1) % size_;
//        out_ += 1;
//        return true;
//    }
//
//    inline std::size_t get_size() {
//        return data_.size();
//    }

private:
    static inline consteval size_type find_capacity() {
        constexpr size_type min_size = 4096 / sizeof(value_type);
        constexpr size_type n = std::min({min_size, N});
        if constexpr ((n & (n - 1)) == 0) {
            return n;
        }
        return (1 << (64 - __builtin_clzl(N)));
    }

    size_type front_index;
    size_type end_index;
    std::array<T, find_capacity()> data_;
    const size_type mask_ = data_.size() - 1;

};
