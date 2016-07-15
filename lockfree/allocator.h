#ifndef HOIST_LOCKFREE_ALLOCATOR_H
#define HOIST_LOCKFREE_ALLOCATOR_H

#include <memory>

namespace hoist {
namespace lockfree {
namespace detail {

const auto atomic_isolation = LFDS710_PAL_ATOMIC_ISOLATION_IN_BYTES;

template<std::size_t N>
class allocator {
public:
    allocator() = default;

    allocator(const allocator &) = delete;

    allocator(allocator &&other) = delete;

    template<class T>
    T *aligned_alloc(std::size_t a = atomic_isolation) {
        if (!std::align(a, sizeof(T), p, sz)) {
            return nullptr;
        }

        T *result = reinterpret_cast<T *>(p);
        p = static_cast<char *>(p) + sizeof(T);
        sz -= sizeof(T);
        return result;
    }

private:
    int8_t data[N];
    void *p = data;
    std::size_t sz = N;
};

}
}
}

#endif //HOIST_LOCKFREE_ALLOCATOR_H
