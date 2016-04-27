#ifndef UTILS_BIGINTEGER_H
#define UTILS_BIGINTEGER_H

#include <string>
#include <type_traits>

#include <gmp.h>

namespace hoist {

class BigInteger {
public:

    // ctors and dtor
    BigInteger();

    template<class Int, typename std::enable_if<
        std::is_fundamental<Int>::value &&
        std::is_integral<Int>::value &&
        std::is_signed<Int>::value,
    Int>::type = 0>
    BigInteger(Int value)
    {
        mpz_init_set_si(mpz, value);
    }

    template<class UInt, typename std::enable_if<
        std::is_fundamental<UInt>::value &&
        std::is_integral<UInt>::value &&
        not std::is_signed<UInt>::value,
    UInt>::type = 0>
    BigInteger(UInt value)
    {
        mpz_init_set_ui(mpz, value);
    }

    BigInteger(double value);

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

    friend BigInteger operator<<(BigInteger lhs, unsigned long int rhs);

    BigInteger& operator<<=(unsigned long int rhs);

    friend BigInteger operator>>(BigInteger lhs, unsigned long int rhs);

    BigInteger& operator>>=(unsigned long int rhs);

    // conversion
    explicit operator int() const;

    explicit operator unsigned int() const;

    explicit operator double() const;

    explicit operator std::string() const;

private:
    mpz_t mpz;
};

}

#endif /* UTILS_BIGINTEGER_H */
