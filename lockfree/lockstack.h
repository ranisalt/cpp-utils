#ifndef LOCKFREE_LOCKSTACK_H
#define LOCKFREE_LOCKSTACK_H

#include <array>
#include <mutex>

namespace hoist {
namespace lockfree {

template<class T, std::size_t Capacity>
class lockstack {
public:
    using const_reference = const T&;
    using reference = T&;
    using size_type = std::size_t;
    using value_type = T;

    lockstack() = default;

    /* accessors */
    reference top() { return buffer[size_ - 1]; }

    const_reference top() const { return buffer[size_ - 1]; }

    /* capacity */
    bool empty() const { return size_ == 0; }

    size_type size() const { return size_; }

    constexpr size_type max_size() const { return Capacity; }

    /* modifiers */
    void push(const value_type& value) {
        std::lock_guard<decltype(mutex)> guard{mutex};
        buffer[size_++] = value;
    }

    void push(value_type&& value) {
        std::lock_guard<decltype(mutex)> guard{mutex};
        buffer[size_++] = std::move(value);
    }

    template<class ...Args>
    void emplace(Args&& ...args) {
        std::lock_guard<decltype(mutex)> guard{mutex};
        buffer[size_++] = {std::forward<Args>(args)...};
    }

    void pop() {
        std::lock_guard<decltype(mutex)> guard{mutex};
        std::move(buffer[--size_]);
    }

private:
    std::mutex mutex;
    std::array<T, Capacity> buffer{};
    std::size_t size_{0};
};

}
}

#endif //LOCKFREE_LOCKSTACK_H
