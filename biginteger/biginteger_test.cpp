#include <gtest/gtest.h>
#include "biginteger.h"

using hoist::BigInteger;

class biginteger_test : public testing::Test {
public:
	BigInteger bi;
};

TEST_F(biginteger_test, isDefaultConstructedToZero) {
    auto zero = BigInteger{0};

	EXPECT_EQ(zero, bi);
}

TEST_F(biginteger_test, equal) {
    auto twenty = BigInteger{20};
    auto other_twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};

    EXPECT_TRUE(twenty == other_twenty);
    EXPECT_FALSE(twenty == twenty_one);
}

TEST_F(biginteger_test, different) {
    auto twenty = BigInteger{20};
    auto other_twenty = BigInteger{20};
    auto not_twenty = BigInteger{21};

    EXPECT_FALSE(twenty != other_twenty);
    EXPECT_TRUE(twenty != not_twenty);
}

TEST_F(biginteger_test, greaterThan) {
    auto twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};

    EXPECT_TRUE(twenty_one > twenty);
}

TEST_F(biginteger_test, lessThan) {
    auto twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};

    EXPECT_TRUE(twenty < twenty_one);
}

TEST_F(biginteger_test, greaterThanOrEqual) {
    auto twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};

    EXPECT_TRUE(twenty_one >= twenty);
}

TEST_F(biginteger_test, lessThanOrEqual) {
    auto twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};

    EXPECT_TRUE(twenty <= twenty_one);
}

TEST_F(biginteger_test, assignInt) {
    auto twenty = BigInteger{20};
    twenty = -20;

    EXPECT_EQ(-20, twenty);
}

TEST_F(biginteger_test, assignCopy) {
    auto twenty = BigInteger{20};
    auto minus_twenty = BigInteger{-20};
    twenty = minus_twenty;

    EXPECT_EQ(minus_twenty, twenty);
}

TEST_F(biginteger_test, assignMove) {
    auto twenty = BigInteger{20};
    auto minus_twenty = BigInteger{-20};
    twenty = std::move(minus_twenty);

    EXPECT_EQ(-20, twenty);
}

TEST_F(biginteger_test, swap) {
    auto twenty = BigInteger{20};
    auto minus_twenty = BigInteger{-20};
    std::swap(twenty, minus_twenty);

    EXPECT_EQ(-20, twenty);
}

TEST_F(biginteger_test, negate) {
    auto twenty = BigInteger{20};
    auto minus_twenty = BigInteger{-20};

    EXPECT_EQ(minus_twenty, -twenty);
}

TEST_F(biginteger_test, addition) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto seventy = BigInteger{70};

    EXPECT_EQ(seventy, twenty + fifty);
}

TEST_F(biginteger_test, subtraction) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto minus_thirty = BigInteger{-30};
    auto thirty = BigInteger{30};

    EXPECT_EQ(minus_thirty, twenty - fifty);
    EXPECT_EQ(thirty, fifty - twenty);
}

TEST_F(biginteger_test, multiplication) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto thousand = BigInteger{1000};

    EXPECT_EQ(thousand, twenty * fifty);
}

TEST_F(biginteger_test, division) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto thousand = BigInteger{1000};

    EXPECT_EQ(twenty, thousand / fifty);
}

TEST_F(biginteger_test, modulus) {
    auto ten = BigInteger{10};
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};

    EXPECT_EQ(ten, fifty % twenty);
}

TEST_F(biginteger_test, power) {
    auto two = BigInteger{2};
    auto one_mega = BigInteger{1048576};

    EXPECT_EQ(one_mega, two.pow(20));
}

TEST_F(biginteger_test, increment) {
    auto twenty = BigInteger{20};
    auto other_twenty = twenty;
    auto twenty_one = BigInteger{21};
    auto twenty_two = BigInteger{22};

    EXPECT_EQ(other_twenty, twenty++);
    EXPECT_EQ(twenty_one, twenty);
    EXPECT_EQ(twenty_two, ++twenty);
    EXPECT_EQ(twenty_two, twenty);
}

TEST_F(biginteger_test, decrement) {
    auto twenty = BigInteger{20};
    auto other_twenty = twenty;
    auto nineteen = BigInteger{19};
    auto eighteen = BigInteger{18};

    EXPECT_EQ(other_twenty, twenty--);
    EXPECT_EQ(nineteen, twenty);
    EXPECT_EQ(eighteen, --twenty);
    EXPECT_EQ(eighteen, twenty);
}

TEST_F(biginteger_test, booleanCast) {
    auto zero = BigInteger{0};
    auto twenty = BigInteger{20};

    EXPECT_FALSE(!twenty);
    EXPECT_TRUE(!zero);
}

TEST_F(biginteger_test, bitAnd) {
    auto twenty_one = BigInteger{21}; // 10101
    auto twenty_two = BigInteger{22}; // 10110
    auto twenty = BigInteger{20};     // 10100

    EXPECT_EQ(twenty, twenty_one & twenty_two);
}

TEST_F(biginteger_test, bitOr) {
    auto twenty_one = BigInteger{21};   // 10101
    auto twenty_two = BigInteger{22};   // 10110
    auto twenty_three = BigInteger{23}; // 10111

    EXPECT_EQ(twenty_three, twenty_one | twenty_two);
}

TEST_F(biginteger_test, bitXor) {
    auto twenty_one = BigInteger{21}; // 10101
    auto twenty_two = BigInteger{22}; // 10110
    auto three = BigInteger{3};       // 00011

    EXPECT_EQ(three, twenty_one ^ twenty_two);
}

TEST_F(biginteger_test, bitComplement) {
    auto twenty = BigInteger{20};            // 10101
    auto minus_twenty_one = BigInteger{-21}; // 10101

    EXPECT_EQ(minus_twenty_one, ~twenty);
}

TEST_F(biginteger_test, intCasting) {
    auto twenty = BigInteger{20};
    int twenty_int = static_cast<int>(twenty);

    EXPECT_EQ(20, twenty_int);
}

TEST_F(biginteger_test, uintCasting) {
    auto twenty = BigInteger{20};
    int twenty_uint = static_cast<unsigned int>(twenty);

    EXPECT_EQ(20, twenty_uint);
}

TEST_F(biginteger_test, stringCasting) {
    auto twenty = BigInteger{20};
    auto twenty_str = std::string(twenty);

    EXPECT_EQ("20", twenty_str);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
