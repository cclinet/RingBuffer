#include <gtest/gtest.h>
#include "ring_buffer.hpp"

// Demonstrate some basic assertions.
TEST(RingBuffer, BasicAssertions) {
    auto ring_buffer = RingBuffer<int, 9>();
    EXPECT_EQ(ring_buffer.size(), 16);
    std::vector<int> insert_data{1, 2, 3};
    ring_buffer.in(insert_data.data(), insert_data.size());

    int v;
    ring_buffer.out(&v);
    EXPECT_EQ(v, 1);
    int vs[2]{};
    ring_buffer.out(&v, 2);
    EXPECT_EQ(vs[0], 2);
    EXPECT_EQ(vs[1], 3);
//    EXPECT_EQ(vs, [2,3]);
    EXPECT_TRUE(ring_buffer.empty());
}
