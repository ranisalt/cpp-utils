#include <algorithm>
#include <iterator>

#include "range.h"

namespace hoist {
namespace detail {

range_iterator& range_iterator::operator++()
{
    auto minmax = std::minmax(current + owner.step, owner.stop);
    current = owner.step > 0 ? minmax.first : minmax.second;
    return *this;
}

range_iterator range_iterator::operator++(int)
{
    auto old = current;
    this->operator++();
    return {old, owner};
}

bool operator==(const range_iterator& lhs, const range_iterator& rhs)
{
    return lhs.owner == rhs.owner and lhs.current == rhs.current;
}

bool operator!=(const range_iterator& lhs, const range_iterator& rhs)
{
    return not operator==(lhs, rhs);
}

}

detail::range_iterator range::begin() const
{
    return {start, *this};
}

detail::range_iterator range::end() const
{
    return {stop, *this};
}

}
