#include <gtest/gtest.h>

#include "stack.h"

using hoist::lockfree::stack;

struct lockfree_stack_test : public testing::Test {
    stack<int> s;
};

TEST_F(lockfree_stack_test, constructor) {
    EXPECT_EQ(0, s.size());
    EXPECT_TRUE(s.empty());
}

TEST_F(lockfree_stack_test, pushLvalue) {
    const int forty_two = 42;
    const int one_thousand_nine_hundred_sixty_three = 1963;
    s.push(forty_two);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(forty_two, s.top());
    s.push(one_thousand_nine_hundred_sixty_three);
    EXPECT_EQ(one_thousand_nine_hundred_sixty_three, s.top());
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_stack_test, pushRvalue) {
    s.push(42);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(42, s.top());
    s.push(1963);
    EXPECT_EQ(2, s.size());
    EXPECT_EQ(1963, s.top());
}

TEST_F(lockfree_stack_test, emplace) {
    s.emplace(42);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(42, s.top());
    s.emplace(1963);
    EXPECT_EQ(1963, s.top());
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_stack_test, pop) {
    s.push(42);
    s.push(1963);
    ASSERT_EQ(2, s.size());
    s.pop();
    EXPECT_EQ(42, s.top());
    EXPECT_EQ(1, s.size());
}

TEST_F(lockfree_stack_test, empty) {
    s.push(42);
    EXPECT_FALSE(s.empty());
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST_F(lockfree_stack_test, top) {
    s.push(42);
    EXPECT_EQ(42, s.top());
    s.push(1963);
    EXPECT_EQ(1963, s.top());
    s.pop();
    EXPECT_EQ(42, s.top());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
