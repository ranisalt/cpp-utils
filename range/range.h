#ifndef RANGE_H
#define RANGE_H

#include <cstdint>

namespace hoist {

class range;

namespace detail {

struct range_iterator: std::iterator_traits<std::intmax_t> {
    range_iterator(std::intmax_t current, const range& owner)
            :current{current}, owner{owner} { }

    range_iterator& operator++();

    range_iterator operator++(int);

    std::intmax_t operator*() { return current; }

    friend bool operator==(const range_iterator& lhs, const range_iterator& rhs);

    friend bool operator!=(const range_iterator& lhs, const range_iterator& rhs);

private:
    std::intmax_t current;
    const range& owner;
};

}

class range {
public:
    range(std::intmax_t stop) :start{0}, stop{stop}, step{1} { }
    range(std::intmax_t start, std::intmax_t stop, std::intmax_t step = 1) :
            start{start}, stop{stop}, step{step} { }

    detail::range_iterator begin() const;

    detail::range_iterator end() const;

    friend bool operator==(const range& lhs, const range& rhs)
    {
        return lhs.start == rhs.start and lhs.stop == rhs.stop and
                lhs.step == rhs.step;
    }

    const std::intmax_t start, stop, step;
};

}

#endif /* RANGE_H */
