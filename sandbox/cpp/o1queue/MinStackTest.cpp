#include "MinStack.hpp"

#include <gtest/gtest.h>

TEST(MinStack, Simple)
{
    MinStack<int> s;
    EXPECT_TRUE(s.empty());

    s.push(5);
    // 5
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.min(), 5);

    s.push(1);
    // 5, 1
    EXPECT_EQ(s.min(), 1);

    s.push(2);
    // 5, 1, 2
    EXPECT_EQ(s.min(), 1);

    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
    // 5
    EXPECT_EQ(s.min(), 5);

    EXPECT_EQ(s.pop(), 5);
    EXPECT_TRUE(s.empty());
}
