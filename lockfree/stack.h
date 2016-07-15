#ifndef HOIST_LOCKFREE_STACK_H
#define HOIST_LOCKFREE_STACK_H

extern "C" {
#include "liblfds710.h"
};

#include "allocator.h"

namespace hoist {
namespace lockfree {

template<class T>
class stack {
    using state = lfds710_stack_state;

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = const reference;

    stack() : ss{new(alloc.aligned_alloc<state>()) state} {
        lfds710_stack_init_valid_on_current_logical_core(ss, nullptr);
    }

    stack(const stack &) = delete;

    stack(stack &&) = delete;

    virtual ~stack() {
        lfds710_stack_cleanup(ss, [](state *ss, lfds710_stack_element *se) {
            delete static_cast<value_type *>(se->value);
            delete se;
        });
    }

    reference top() {
        return *static_cast<value_type *>(ss->top[POINTER]->value);
    }

    const_reference top() const {
        return *static_cast<value_type *>(ss->top[POINTER]->value);
    }

    bool empty() const {
        return size() == 0;
    }

    size_type size() const {
        lfds710_pal_uint_t size_;
        lfds710_stack_query(ss, LFDS710_STACK_QUERY_SINGLETHREADED_GET_COUNT, nullptr, &size_);
        return static_cast<size_type>(size_);
    }

    void push(const value_type &value) {
        lfds710_stack_element *se = new lfds710_stack_element;
        se->value = new T{value};
        lfds710_stack_push(ss, se);
    }

    void push(value_type &&value) {
        lfds710_stack_element *se = new lfds710_stack_element;
        se->value = new T{std::move(value)};
        lfds710_stack_push(ss, se);
    }

    template<class... Args>
    void emplace(Args &&... args) {
        lfds710_stack_element *se = new lfds710_stack_element;
        se->value = new T{std::forward<Args>(args)...};
        lfds710_stack_push(ss, se);
    }

    value_type pop() {
        lfds710_stack_element *se;
        lfds710_stack_pop(ss, &se);
        value_type *ptr = static_cast<value_type *>(se->value);
        value_type value = *ptr;
        delete ptr;
        delete se;
        return value;
    }

private:
    detail::allocator<sizeof(state) + detail::atomic_isolation> alloc;
    state *ss;
};

}
}

#endif //HOIST_LOCKFREE_STACK_H
