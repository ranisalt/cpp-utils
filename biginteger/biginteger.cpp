#include "biginteger.h"

namespace hoist {

BigInteger::BigInteger()
{
    mpz_init(mpz);
}

BigInteger::BigInteger(double value)
{
    mpz_init_set_d(mpz, value);
}

BigInteger::BigInteger(const BigInteger& that)
{
    mpz_init_set(mpz, that.mpz);
}

BigInteger::BigInteger(BigInteger&& that)
{
    mpz_init(mpz);
    swap(that);
}

BigInteger::~BigInteger() {
    mpz_clear(mpz);
}

void BigInteger::swap(BigInteger& that)
{
    mpz_swap(mpz, that.mpz);
}

BigInteger& BigInteger::operator=(const BigInteger& rhs)
{
    mpz_set(mpz, rhs.mpz);
    return *this;
}

BigInteger& BigInteger::operator=(BigInteger&& rhs)
{
    swap(rhs);
    return *this;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
    return mpz_cmp(lhs.mpz, rhs.mpz) == 0;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
    return not (lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs)
{
    return mpz_cmp(lhs.mpz, rhs.mpz) < 0;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs)
{
    return mpz_cmp(lhs.mpz, rhs.mpz) > 0;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs)
{
    return mpz_cmp(lhs.mpz, rhs.mpz) <= 0;
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs)
{
    return mpz_cmp(lhs.mpz, rhs.mpz) >= 0;
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs)
{
    return lhs += rhs;
}

BigInteger operator-(BigInteger that)
{
    mpz_neg(that.mpz, that.mpz);
    return that;
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs)
{
    mpz_add(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator-(BigInteger lhs, const BigInteger& rhs)
{
    return lhs -= rhs;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs)
{
    mpz_sub(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator*(BigInteger lhs, const BigInteger& rhs)
{
    return lhs *= rhs;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs)
{
    mpz_mul(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator/(BigInteger lhs, const BigInteger& rhs)
{
    return lhs /= rhs;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs)
{
    mpz_tdiv_q(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator%(BigInteger lhs, const BigInteger& rhs)
{
    return lhs %= rhs;
}

BigInteger& BigInteger::operator%=(const BigInteger& rhs)
{
    mpz_mod(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger pow(BigInteger base, unsigned long int iexp)
{
    return base.pow(iexp);
}

BigInteger& BigInteger::pow(unsigned long int iexp)
{
    mpz_pow_ui(mpz, mpz, iexp);
    return *this;
}

BigInteger& BigInteger::operator++()
{
    mpz_add_ui(mpz, mpz, 1);
    return (*this);
}

BigInteger BigInteger::operator++(int)
{
    auto tmp = BigInteger{*this};
    ++(*this);
    return tmp;
}

BigInteger& BigInteger::operator--()
{
    mpz_sub_ui(mpz, mpz, 1);
    return (*this);
}

BigInteger BigInteger::operator--(int)
{
    auto tmp = BigInteger{*this};
    --(*this);
    return tmp;
}

bool BigInteger::operator!() const
{
    return mpz_cmp_si(mpz, 0) == 0;
}

BigInteger operator&(BigInteger lhs, const BigInteger& rhs)
{
    return lhs &= rhs;
}

BigInteger& BigInteger::operator&=(const BigInteger& rhs)
{
    mpz_and(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator|(BigInteger lhs, const BigInteger& rhs)
{
    return lhs |= rhs;
}

BigInteger& BigInteger::operator|=(const BigInteger& rhs)
{
    mpz_ior(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator^(BigInteger lhs, const BigInteger& rhs)
{
    return lhs ^= rhs;
}

BigInteger& BigInteger::operator^=(const BigInteger& rhs)
{
    mpz_xor(mpz, mpz, rhs.mpz);
    return *this;
}

BigInteger operator~(BigInteger that)
{
    mpz_com(that.mpz, that.mpz);
    return that;
}

BigInteger::operator int() const
{
    return mpz_get_si(mpz);
}

BigInteger::operator unsigned int() const
{
    return mpz_get_ui(mpz);
}

BigInteger::operator double() const
{
    return mpz_get_d(mpz);
}

BigInteger::operator std::string() const
{
    return mpz_get_str(nullptr, 10, mpz);
}

}
