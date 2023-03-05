#include <gtest/gtest.h>
#include "ring_buffer.hpp"

// Demonstrate some basic assertions.
TEST(RingBuffer, BasicAssertions) {
  auto ring_buffer = RingBuffer<int, 16>();
  ring_buffer.push({1, 2});

  int v;
  ring_buffer.pop(&v);
  EXPECT_EQ(v, 1);
    ring_buffer.pop(&v);
  EXPECT_EQ(v, 2);
}
