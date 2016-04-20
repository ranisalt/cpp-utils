#ifndef skiplist_H
#define skiplist_H

#include <iostream>
#include <list>

namespace hoist {

template<class T>
class skiplist {
    using Container = std::list<T>;

public:
    using const_iterator = typename Container::const_iterator;
    using iterator = typename Container::iterator;
    using size_type = typename Container::size_type;
    using value_type = T;

    /* ctors, dtor and assignment */
    constexpr skiplist() = default;

    explicit skiplist(size_type count, const T& value = T{}):
        container{count, value} {}

    /* element access */

    /* iterators */
    iterator begin() {
        return std::begin(container);
    }

    const_iterator begin() const {
        return std::begin(container);
    }

    iterator end() {
        return std::end(container);
    }

    const_iterator end() const {
        return std::end(container);
    }

    /* capacity */
    bool empty() const noexcept {
        return container.empty();
    }

    std::size_t size() const noexcept {
        return container.size();
    }

    /* modifiers */
    void clear() noexcept {
    }

    void insert(const value_type& value) {
        return container.insert(std::lower_bound(std::begin(container),
                    std::end(container), value), value);
    }

    void insert(value_type&& value) {
    }

    friend std::ostream& operator<<(std::ostream& os, const skiplist& s) {
        os << '[';
        if (!s.empty()) {
            os << *std::begin(s);
            for (auto it = std::next(std::begin(s)); it != std::end(s); ++it) {
                os << ", " << *it;
            }
        }
        os << ']';
        return os;
    }

    template<class Container>
    friend auto make_skiplist(Container&& other) -> skiplist<typename Container::value_type>;

private:
    /* ctors that must be checked */
    template<class InputIt>
    skiplist(InputIt first, InputIt last): container{first, last} {}

    Container container;
};

template<class Container>
auto make_skiplist(Container&& other) -> skiplist<typename Container::value_type>
{
    return {std::begin(other), std::end(other)};
}

}

#endif /* skiplist_H */
