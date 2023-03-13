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


public:
    bool empty() const {
        return end_index >= front_index;
    }

    size_type size() const {
        return data_.size();
    }

public:
    size_type in(T *buf, size_type n = 1) {
        std::copy(buf, buf + n, data_.begin() + front_index);
//        std::memmove(data_.begin()+front_index, buf, n);
        front_index += n;
        return n;
    }

    size_type out(T *buf, size_type n = 1) {
        std::memmove(buf, data_.begin()+end_index, n);
        std::cout<<*buf<<' '<<*(data_.begin()+end_index)<<'\n';
        end_index += n;
        return n;
    }

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
};
