#include <gtest/gtest.h>
#include "statistics.h"

using namespace hoist::statistics;

struct statistics_test: public testing::Test {
    std::vector<int> vec = {
        -39, 49, 63, 65, 7, 57, -41, 40, -79, 29, -91, -73, 66, -59, -77, 32
    };
};

TEST_F(statistics_test, arithmetic_mean) {
    // arithmetic mean is -3.185, C++ performs rounding towards zero
    EXPECT_DOUBLE_EQ(-3.1875, arithmetic_mean(std::begin(vec), std::end(vec)));
    EXPECT_DOUBLE_EQ(-0.8, arithmetic_mean(std::begin(vec) + 1, std::end(vec)));
}

TEST_F(statistics_test, median) {
    EXPECT_DOUBLE_EQ(18.0, median(std::begin(vec), std::end(vec)));
    EXPECT_DOUBLE_EQ(29.0, median(std::begin(vec) + 1, std::end(vec)));
}

TEST_F(statistics_test, standard_deviation) {
    EXPECT_NEAR(58.10, standard_deviation(std::begin(vec), std::end(vec)), 0.01);
    EXPECT_NEAR(59.24, standard_deviation(std::begin(vec) + 1, std::end(vec)), 0.01);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
