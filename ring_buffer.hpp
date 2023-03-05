#pragma once
#include <cstddef>
#include <memory>
#include <concepts>
#include <algorithm>

template <typename T, std::size_t N>
class RingBuffer
{
public:
    RingBuffer() : out_(0), in_(0)
    {
    }
    ~RingBuffer() = default;

    // RingBuffer(const RingBuffer &) = delete;
    // RingBuffer &operator=(const RingBuffer &) = delete;

    // RingBuffer(RingBuffer &&other) : out_(other.out_), in_(other.in_), data_(std::move(other.data_)) {}
    // RingBuffer &operator=(RingBuffer &&other)
    // {
    //     *this = std::move(other);
    // }

    inline std::size_t unused() const
    {
        return N - (in_ - out_);
    }

    inline bool push(std::initializer_list<T> buf)
    {
        if (unused() < buf.size())
        {
            return false;
        }
        std::size_t off = in_ & mask_;
        std::size_t l = std::min(buf.size(), N - off);
        std::copy(buf.begin(), buf.begin() + l, std::begin(data_) + in_);
        std::copy(buf.begin() + l, buf.end(), std::begin(data_));

        in_ += buf.size();
        return true;
    }

    inline bool pop(T *value)
    {
        *value = data_[out_];
        // if (is_empty())
        // {
        //     return false;
        // }
        // *value = data_[out_];
        // out_ = (out_ + 1) % size_;
        out_ += 1;
        return true;
    }

private:
    std::size_t out_;
    std::size_t in_;
    const std::size_t mask_ = N - 1;
    std::array<T, N> data_;
};
