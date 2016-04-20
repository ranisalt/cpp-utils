#ifndef UTILS_BIGINTEGER_H
#define UTILS_BIGINTEGER_H

#include <cstdint>
#include <string>

#include <gmp.h>

namespace hoist {

class BigInteger {
public:

    // ctors and dtor
    BigInteger(int32_t value = 0);

    BigInteger(const BigInteger& that);

    BigInteger(BigInteger&& that);

    ~BigInteger();

    void swap(BigInteger& that);

    // comparison
    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

    // arithmetic
    BigInteger& operator=(int32_t rhs);

    BigInteger& operator=(const BigInteger& rhs);

    BigInteger& operator=(BigInteger&& rhs);

    friend BigInteger operator-(BigInteger that);

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

    friend BigInteger pow(const BigInteger& base, unsigned long int iexp);

    BigInteger& pow(unsigned long int iexp);

    // increment and decrement
    BigInteger& operator++();

    BigInteger operator++(int);

    BigInteger& operator--();

    BigInteger operator--(int);

    // logical
    bool operator!() const;

    // bitwise
    friend BigInteger operator&(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator&=(const BigInteger& rhs);

    friend BigInteger operator|(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator|=(const BigInteger& rhs);

    friend BigInteger operator^(BigInteger lhs, const BigInteger& rhs);

    BigInteger& operator^=(const BigInteger& rhs);

    friend BigInteger operator~(BigInteger lhs);

    // conversion
    explicit operator int() const;

    explicit operator unsigned int() const;

    explicit operator std::string() const;

private:
    mpz_t mpz;
};

}

#endif /* UTILS_BIGINTEGER_H */
