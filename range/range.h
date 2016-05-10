#ifndef RANGE_H
#define RANGE_H

#include <algorithm>
#include <iterator>

namespace my {

class range {
    struct iterator: std::iterator_traits<int> {
        iterator(int current, const range& owner):
            current{current}, owner{owner} {}

        iterator& operator++() {
            auto minmax = std::minmax(current + owner.step, owner.stop);
            current = owner.step > 0 ? minmax.first : minmax.second;
            return *this;
        }

        iterator operator++(int) {
            auto old = current;
            ++(*this);
            return {old, owner};
        }

        int operator*() const {
            return current;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.owner == rhs.owner and lhs.current == rhs.current;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return not (lhs.current == rhs.current);
        }

    private:
        int current;
        const range& owner;
    };

public:
    range(int stop): start{0}, stop{stop}, step{1} {}
    range(int start, int stop, int step = 1):
        start{start}, stop{stop}, step{step} {}

    iterator begin() const {
        return {start, *this};
    }

    iterator end() const {
        return {stop, *this};
    }

    friend bool operator==(const range& lhs, const range& rhs) {
        return lhs.start == rhs.start and lhs.stop == rhs.stop and
            lhs.step == rhs.step;
    }

    const int start, stop, step;
};

}

#endif /* RANGE_H */
