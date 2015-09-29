#include "mbi.h"

namespace utils {

int32_t BigInteger::get_high(int64_t value)
{
    return static_cast<int32_t>(value >> 32);
}

int32_t BigInteger::get_low(int64_t value)
{
    return static_cast<int32_t>(value & lower_mask);
}

BigInteger::BigInteger(int32_t value) :
    digits{value,}, signal{value < 0}
{
}

BigInteger::BigInteger(int64_t value) :
    digits{get_low(value), get_high(value)}, signal{value < 0}
{
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
    return lhs.digits == rhs.digits;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
    return lhs.digits != rhs.digits;
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs)
{
    return lhs += rhs;
}

BigInteger operator-(BigInteger lhs, const BigInteger& rhs)
{
    return lhs -= rhs;
}

BigInteger operator*(BigInteger lhs, const BigInteger& rhs)
{
    return lhs *= rhs;
}

BigInteger operator/(BigInteger lhs, const BigInteger& rhs)
{
    return lhs /= rhs;
}

BigInteger operator%(BigInteger lhs, const BigInteger& rhs)
{
    return lhs %= rhs;
}

BigInteger& BigInteger::operator++()
{
    return (*this) += 1;
}

BigInteger BigInteger::operator++(int)
{
    auto tmp = BigInteger{*this};
    ++(*this);
    return tmp;
}

BigInteger& BigInteger::operator--()
{
    return (*this) -= 1;
}

BigInteger BigInteger::operator--(int)
{
    auto tmp = BigInteger{*this};
    --(*this);
    return tmp;
}

bool BigInteger::operator!() const
{
    return digits.size() != 1 or digits[0] != 0;
}

}
