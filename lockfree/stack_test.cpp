#include <gtest/gtest.h>
#include "stack.h"

using hoist::lockfree::stack;

struct lockfree_stack_test: public testing::Test
{
    stack<int> s;
};

TEST_F(lockfree_stack_test, isCreatedEmpty) {
    EXPECT_EQ(0, s.size());
}

TEST_F(lockfree_stack_test, pushLvalueStacks) {
    const int forty_two = 42;
    const int one_thousand_nine_hundred_sixty_three = 1963;
    s.push(forty_two);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(forty_two, s.top());
    s.push(one_thousand_nine_hundred_sixty_three);
    EXPECT_EQ(one_thousand_nine_hundred_sixty_three, s.top());
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_stack_test, pushRvalueStacks) {
    s.push(42);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(42, s.top());
    s.push(1963);
    EXPECT_EQ(1963, s.top());
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_stack_test, emplaceStacks) {
    s.emplace(42);
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(42, s.top());
    s.emplace(1963);
    EXPECT_EQ(1963, s.top());
    EXPECT_EQ(2, s.size());
}

TEST_F(lockfree_stack_test, popUnstacks) {
    s.push(42);
    s.push(1963);
    s.pop();
    EXPECT_EQ(42, s.top());
    EXPECT_EQ(1, s.size());
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
