#include <gtest/gtest.h>
#include "ring_buffer.hpp"

// Demonstrate some basic assertions.
TEST(RingBuffer, BasicAssertions) {
    auto ring_buffer = RingBuffer<int, 3>();
    EXPECT_EQ(ring_buffer.size(), 4);
    std::vector<int> insert_data{1, 2, 3, 4};
    ring_buffer.in(insert_data.data(), insert_data.size());

    int v;
    ring_buffer.out(&v);
    EXPECT_EQ(v, 1);
    int vs[4]{};
    ring_buffer.out(vs, 2);
    EXPECT_EQ(vs[0], 2);
    EXPECT_EQ(vs[1], 3);

    std::vector<int> insert_data2{5,6,7};
    ring_buffer.in(insert_data2.data(), insert_data2.size());

    ring_buffer.out(vs, 4);
    EXPECT_EQ(vs[0], 4);
    EXPECT_EQ(vs[1], 5);
    EXPECT_EQ(vs[2], 6);
    EXPECT_EQ(vs[3], 7);

    EXPECT_TRUE(ring_buffer.empty());
}
