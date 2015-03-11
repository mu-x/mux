#include "MinQueue.hpp"

#include <gtest/gtest.h>

TEST(MinQueue, Simple)
{
    MinQueue<int> q;
    EXPECT_TRUE(q.empty());

    q.push(1);
    q.push(3);
    q.push(2);
    // 1, 3, 2
    EXPECT_EQ(q.min(), 1);

    EXPECT_EQ(q.pop(), 1);
    // 3, 2
    EXPECT_EQ(q.min(), 2);

    EXPECT_EQ(q.pop(), 3);
    // 2
    EXPECT_EQ(q.min(), 2);

    q.push(-1);
    // 2, -1
    EXPECT_EQ(q.min(), -1);

    q.push(0);
    // 2, -1, 0
    EXPECT_EQ(q.min(), -1);

    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), -1);
    // 0
    EXPECT_EQ(q.min(), 0);

    EXPECT_EQ(q.pop(), 0);
    EXPECT_TRUE(q.empty());
}
