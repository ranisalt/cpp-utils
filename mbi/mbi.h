#ifndef UTILS_BIGINTEGER_H
#define UTILS_BIGINTEGER_H

#include <cstdint>
#include <string>

#include <gmp.h>

namespace my {

class BigInteger {
public:

    // ctors and dtor
    BigInteger(int32_t value = 0);

    BigInteger(const BigInteger& that);

    ~BigInteger();

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
    mpz_t mpz;
};

}

#endif /* UTILS_BIGINTEGER_H */
