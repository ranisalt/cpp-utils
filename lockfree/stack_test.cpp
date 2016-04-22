#include <gtest/gtest.h>
#include "stack.h"

using hoist::lockfree::stack;

struct lockfree_stack_test: public testing::Test
{
    stack<int, 10> lfstack;
};

TEST_F(lockfree_stack_test, isCreatedEmpty) {
    EXPECT_EQ(0, lfstack.size());
}

TEST_F(lockfree_stack_test, pushLvalueStacks) {
    const int forty_two = 42;
    const int one_thousand_nine_hundred_sixty_three = 1963;
    lfstack.push(forty_two);
    EXPECT_EQ(1, lfstack.size());
    EXPECT_EQ(forty_two, lfstack.top());
    lfstack.push(one_thousand_nine_hundred_sixty_three);
    EXPECT_EQ(one_thousand_nine_hundred_sixty_three, lfstack.top());
    EXPECT_EQ(2, lfstack.size());
}

TEST_F(lockfree_stack_test, pushRvalueStacks) {
    lfstack.push(42);
    EXPECT_EQ(1, lfstack.size());
    EXPECT_EQ(42, lfstack.top());
    lfstack.push(1963);
    EXPECT_EQ(1963, lfstack.top());
    EXPECT_EQ(2, lfstack.size());
}

TEST_F(lockfree_stack_test, emplaceStacks) {
    lfstack.emplace(42);
    EXPECT_EQ(1, lfstack.size());
    EXPECT_EQ(42, lfstack.top());
    lfstack.emplace(1963);
    EXPECT_EQ(1963, lfstack.top());
    EXPECT_EQ(2, lfstack.size());
}

TEST_F(lockfree_stack_test, popUnstacks) {
    lfstack.push(42);
    lfstack.push(1963);
    lfstack.pop();
    EXPECT_EQ(42, lfstack.top());
    EXPECT_EQ(1, lfstack.size());
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
