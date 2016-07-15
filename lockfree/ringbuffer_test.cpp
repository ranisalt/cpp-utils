#include <gtest/gtest.h>

#include "../range/range.h"
#include "ringbuffer.h"

using hoist::lockfree::ringbuffer;
using hoist::range;

struct lockfree_ringbuffer_test: public testing::Test
{
    ringbuffer<intmax_t, 4> s;
};

TEST_F(lockfree_ringbuffer_test, constructor) {
    EXPECT_EQ(0, s.size());
}

TEST_F(lockfree_ringbuffer_test, pushLvalue) {
    const int forty_two = 42;
    const int one_thousand_nine_hundred_sixty_three = 1963;
    s.push(forty_two);
    EXPECT_EQ(1, s.size());
    s.push(one_thousand_nine_hundred_sixty_three);
    EXPECT_EQ(2, s.size());
    EXPECT_EQ(42, s.pop());
    EXPECT_EQ(1963, s.pop());
}

TEST_F(lockfree_ringbuffer_test, pushRvalue) {
    s.push(42);
    EXPECT_EQ(1, s.size());
    s.push(1963);
    EXPECT_EQ(2, s.size());
    EXPECT_EQ(42, s.pop());
    EXPECT_EQ(1963, s.pop());
}

TEST_F(lockfree_ringbuffer_test, emplace) {
    s.emplace(42);
    EXPECT_EQ(1, s.size());
    s.emplace(1963);
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_ringbuffer_test, pop) {
    s.push(42);
    s.push(1963);
    ASSERT_EQ(2, s.size());
    s.pop();
    EXPECT_EQ(1, s.size());
}

TEST_F(lockfree_ringbuffer_test, bad_good) {
    for (auto i: range(4)) {
        s.push(i);
    }
    ASSERT_FALSE(s.bad());
    ASSERT_TRUE(s.good());
    s.push(42);
    EXPECT_TRUE(s.bad());
    EXPECT_FALSE(s.good());
}

TEST_F(lockfree_ringbuffer_test, overridden) {
    for (auto i: range(4)) {
        s.push(i);
    }
    s.push(42);
    EXPECT_EQ(0, s.overridden());
    s.push(1963);
    EXPECT_EQ(1, s.overridden());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
