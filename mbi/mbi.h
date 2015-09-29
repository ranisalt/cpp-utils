#include <cstdint>
#include <vector>

#ifndef UTILS_BIGINTEGER_H
#define UTILS_BIGINTEGER_H

#include <string>

namespace utils {

class BigInteger {
    // masks
    const static int64_t lower_mask = 0x00000000FFFFFFFF;

    static inline int32_t get_low(int64_t value);

    static inline int32_t get_high(int64_t value);

public:

    // ctors
    BigInteger() = default;

    BigInteger(int32_t value);

    BigInteger(int64_t value);

    // comparison
    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);

    // arithmetic
    friend BigInteger operator+(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator+=(const BigInteger& rhs);

    friend BigInteger operator-(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator-=(const BigInteger& rhs);

    friend BigInteger operator*(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator*=(const BigInteger& rhs);

    friend BigInteger operator/(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator/=(const BigInteger& rhs);

    friend BigInteger operator%(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator%=(const BigInteger& rhs);

    // increment and decrement
    BigInteger& operator++();

    BigInteger operator++(int);

    BigInteger& operator--();

    BigInteger operator--(int);

    // logical
    bool operator!() const;

    // conversion
    explicit operator std::string() const;

private:
    std::vector<int32_t> digits{0,};
    bool signal{false};
};

}

#endif /* UTILS_BIGINTEGER_H */
