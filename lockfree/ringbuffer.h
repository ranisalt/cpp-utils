#ifndef HOIST_LOCKFREE_RINGBUFFER_H
#define HOIST_LOCKFREE_RINGBUFFER_H

extern "C" {
#include "liblfds710.h"
};

#include "allocator.h"

namespace hoist {
namespace lockfree {

template<class T, std::size_t N>
class ringbuffer {
    using state = lfds710_ringbuffer_state;

    static_assert(N != 0, "Number of elements must be positive.");

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = const reference;

    ringbuffer() : rs{new(alloc.aligned_alloc<state>()) state}, re{} {
        lfds710_ringbuffer_init_valid_on_current_logical_core(rs, re, N + 1, nullptr);
    }

    ~ringbuffer() {
        lfds710_ringbuffer_cleanup(rs, [](state *rs, void *, void *value, lfds710_misc_flag) {
            delete static_cast<value_type *>(value);
        });
    }

    size_type size() const {
        lfds710_pal_uint_t size_;
        lfds710_ringbuffer_query(rs, LFDS710_RINGBUFFER_QUERY_SINGLETHREADED_GET_COUNT, nullptr, &size_);
        return static_cast<size_type>(size_);
    }

    void push(const value_type &value) {
        value_type *ptr = new value_type{value};
        lfds710_ringbuffer_write(rs, nullptr, ptr, nullptr, nullptr, nullptr);
    }

    void push(value_type &&value) {
        value_type *ptr = new value_type{std::move(value)};
        lfds710_ringbuffer_write(rs, nullptr, ptr, nullptr, nullptr, nullptr);
    }

    template<class... Args>
    void emplace(Args &&... args) {
        value_type *ptr = new value_type{std::forward<Args>(args)...};
        lfds710_ringbuffer_write(rs, nullptr, ptr, nullptr, nullptr, nullptr);
    }

    value_type pop() {
        void *re;
        lfds710_ringbuffer_read(rs, nullptr, &re);
        value_type value = *static_cast<value_type *>(re);
        return value;
    }

private:
    detail::allocator<sizeof(state) + detail::atomic_isolation> alloc;
    state *rs;
    lfds710_ringbuffer_element re[N + 1];
};

}
}

#endif //HOIST_LOCKFREE_RINGBUFFER_H
