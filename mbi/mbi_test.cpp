#include <gtest/gtest.h>
#include "mbi.h"

using utils::BigInteger;

class mbi_test : public testing::Test {
public:
	BigInteger bi;
};

TEST_F(mbi_test, isDefaultConstructedToZero) {
    auto zero = BigInteger{0};

	EXPECT_EQ(zero, bi);
}

TEST_F(mbi_test, equal) {
    auto twenty = BigInteger{20};
    auto other_twenty = BigInteger{20};

    EXPECT_EQ(twenty, other_twenty);
}

TEST_F(mbi_test, different) {
    auto twenty = BigInteger{20};
    auto not_twenty = BigInteger{21};

    EXPECT_NE(twenty, not_twenty);
}

TEST_F(mbi_test, addition) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto seventy = BigInteger{70};

    EXPECT_EQ(seventy, twenty + fifty);
}

TEST_F(mbi_test, subtraction) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto minus_thirty = BigInteger{-30};
    auto thirty = BigInteger{30};

    EXPECT_EQ(minus_thirty, twenty - fifty);
    EXPECT_EQ(thirty, fifty - twenty);
}

TEST_F(mbi_test, multiplication) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto thousand = BigInteger{1000};

    EXPECT_EQ(thousand, twenty * fifty);
}

TEST_F(mbi_test, division) {
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};
    auto thousand = BigInteger{1000};

    EXPECT_EQ(twenty, thousand / fifty);
}

TEST_F(mbi_test, modulus) {
    auto ten = BigInteger{10};
    auto twenty = BigInteger{20};
    auto fifty = BigInteger{50};

    EXPECT_EQ(ten, fifty % twenty);
}

TEST_F(mbi_test, increment) {
    auto twenty = BigInteger{20};
    auto twenty_one = BigInteger{21};
    auto twenty_two = BigInteger{22};

    EXPECT_EQ(twenty, twenty++);
    EXPECT_EQ(twenty_one, twenty);
    EXPECT_EQ(twenty_two, ++twenty);
    EXPECT_EQ(twenty_two, twenty);
}

TEST_F(mbi_test, decrement) {
    auto twenty = BigInteger{20};
    auto nineteen = BigInteger{19};
    auto eighteen = BigInteger{18};

    EXPECT_EQ(twenty, twenty--);
    EXPECT_EQ(nineteen, twenty);
    EXPECT_EQ(eighteen, --twenty);
    EXPECT_EQ(eighteen, twenty);
}

TEST_F(mbi_test, booleanCast) {
    auto zero = BigInteger{0};
    auto twenty = BigInteger{20};

    EXPECT_FALSE(!twenty);
    EXPECT_TRUE(!zero);
}
