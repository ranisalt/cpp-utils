#include <gtest/gtest.h>
#include <list>
#include "range.h"

using range = hoist::range;

struct range_test: public testing::Test {
};

TEST_F(range_test, stop) {
    auto r = range{3};

    auto it = std::begin(r);
    EXPECT_EQ(0, *it++);
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(2, *it++);
    EXPECT_EQ(std::end(r), it);
}

TEST_F(range_test, start) {
    auto r = range{5, 8};

    auto it = std::begin(r);
    EXPECT_EQ(5, *it++);
    EXPECT_EQ(6, *it++);
    EXPECT_EQ(7, *it++);
    EXPECT_EQ(std::end(r), it);
}

TEST_F(range_test, step) {
    auto r = range{10, 18, 3};

    auto it = std::begin(r);
    EXPECT_EQ(10, *it++);
    EXPECT_EQ(13, *it++);
    EXPECT_EQ(16, *it++);
    EXPECT_EQ(std::end(r), it);
}

TEST_F(range_test, negativeStep) {
    auto r = range{0, -5, -2};

    auto it = std::begin(r);
    EXPECT_EQ(0, *it++);
    EXPECT_EQ(-2, *it++);
    EXPECT_EQ(-4, *it++);
    EXPECT_EQ(std::end(r), it);
}

TEST_F(range_test, rangeFor) {
    auto r = range{20, 23};
    auto expected = std::list<int>{20, 21, 22};

    for (auto i: r) {
        EXPECT_EQ(expected.front(), i);
        expected.pop_front();
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
