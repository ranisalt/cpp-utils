#ifndef LOCKFREE_STACK_H
#define LOCKFREE_STACK_H

#include <array>

#ifndef RACE_TEST
#include <atomic>
#else
#include "relacy/relacy/relacy.hpp"
#endif

namespace hoist {
namespace lockfree {

template<class T, std::size_t Capacity>
class stack {
public:
    using const_reference = const T&;
    using reference = T&;
    using size_type = std::size_t;
    using value_type = T;

    stack() = default;

#ifdef RACE_TEST
#define size_ size_($)
#endif

    /* accessors */
    reference top() { return buffer[size_ - 1]; }

    const_reference top() const { return buffer[size_ - 1]; }

    /* capacity */
    bool empty() const { return size_ == 0; }

    size_type size() const { return size_; }

    constexpr size_type max_size() const { return Capacity; }

    /* modifiers */
    void push(const value_type& value) {
        buffer[size_++] = value;
    }

    void push(value_type&& value) {
        buffer[size_++] = std::move(value);
    }

    template<class ...Args>
    void emplace(Args&& ...args) {
        buffer[size_++] = {std::forward<Args>(args)...};
    }

    void pop() { std::move(buffer[--size_]); }

#undef size_

private:
#ifndef RACE_TEST
    using atomic_size = std::atomic<size_type>;
#else
    using atomic_size = rl::atomic<size_type>;
#endif

    std::array<T, Capacity> buffer{};
    atomic_size size_{0};
};

}
}

#endif //LOCKFREE_STACK_H
