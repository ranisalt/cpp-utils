#ifndef LOCKFREE_STACK_H
#define LOCKFREE_STACK_H

#include <atomic>
#include <memory>

namespace hoist {
namespace lockfree {

template<class T, class Allocator = std::allocator<T>>
class stack {
    struct node {
        node* next;
        T value;

        node(const T& value):
            value{value} {}

        node(T&& value):
            value{std::move(value)} {}
    };

public:
    using const_reference = const T&;
    using reference = T&;
    using size_type = std::size_t;
    using value_type = T;

    stack() = default;

    //stack(const Allocator& alloc): alloc{alloc} {}

    /* accessors */
    reference top() {
        synchronized {
            return head->value;
        }
    }

    const_reference top() const {
        synchronized {
            return head->value;
        }
    }

    /* capacity */
    bool empty() const { return head != nullptr; }

    size_type size() const { return size_; }

    /* modifiers */
    void push(const value_type& value) {
        auto added = new node(value);
        synchronized {
            added->next = head;
            head = added;
        }
        ++size_;
    }

    void push(value_type&& value) {
        auto added = new node(value);
        synchronized {
            added->next = head;
            head = added;
        }
        ++size_;
    }

    template<class ...Args>
    void emplace(Args&& ...args) {
        auto added = new node(T{std::forward<Args>(args)...});
        synchronized {
            added->next = head;
            head = added;
        }
        ++size_;
    }

    void pop() {
        node* prev;
        synchronized {
            prev = head;
            head = head->next;
        }
        --size_;
        delete prev;
    }

private:
    //Allocator alloc;
    node* head{nullptr};
    std::atomic<size_type> size_{0};
};

}
}

#endif //LOCKFREE_STACK_H
