#ifndef LOCKFREE_STACK_H
#define LOCKFREE_STACK_H

#include <atomic>
#include <memory>

namespace hoist {
namespace lockfree {

template<class T>
class stack {
    struct node {
        node(const T& value, node* next):
                value{value}, next{next} {}
        node(T&& value, node* next):
                value{std::move(value)}, next{next} {}

        // for the sake of alignment
        node* next;
        T value;
    };

public:
    using const_reference = const T&;
    using reference = T&;
    using size_type = std::size_t;
    using value_type = T;

    stack() = default;
    explicit stack(const stack<T>& that);
    explicit stack(stack<T>&& that);

    virtual ~stack() {
    }

    /* accessors */
    reference top() {
        auto* p = head.load();
        return p->value;
    }

    const_reference top() const {
        auto* p = head.load();
        return p->value;
    }

    /* capacity */
    bool empty() const {
        return size_ == 0;
    }

    size_type size() const {
        return size_;
    }

    /* modifiers */
    void push(const value_type& value) {
        auto* p = new node{value, head.load()};
        while (head.compare_exchange_weak(p->next, p));
        ++size_;
    }

    void push(value_type&& value) {
        auto* p = new node{std::move(value), head.load()};
        while (head.compare_exchange_weak(p->next, p));
        ++size_;
    }

    template<class ...Args>
    void emplace(Args&& ...args) {
        auto* p = new node{std::forward<Args>(args)..., head.load()};
        while (head.compare_exchange_weak(p->next, p));
        ++size_;
    }

    void pop() {
        auto* p = head.load();
        while (p && head.compare_exchange_weak(p, p->next));
        delete p;
        --size_;
    }

private:
    std::atomic<node*> head{nullptr};
    std::atomic<size_type> size_{0};
};

}
}

#endif //LOCKFREE_STACK_H
