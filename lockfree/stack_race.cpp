#include <atomic>
#include <iostream>
#include "relacy/relacy/relacy.hpp"

#define RACE_TEST
#include "stack.h"

using hoist::lockfree::stack;
constexpr auto stack_size = 256;

/* maximum number of threads guaranteed to be fed */
constexpr auto thread_num = stack_size / 2;

struct Object
{
    int id;
    const char* name;

    Object(int id, const char* name): id{id}, name{name} {}
};

struct lockfree_race_test: public rl::test_suite<lockfree_race_test, thread_num>
{
    stack<Object> s;
    std::atomic<int> finished{-1};

    void before() {
        for (auto i = 0; i < stack_size / 2; ++i) {
            s.emplace(i, "Test object");
        }
        ++finished;
    }

    void thread(int thread_idx) {
        /* hold all threads until stack is filled */
        while (finished < 0);
        if (thread_idx & 1) {
            s.pop();
        } else {
            if (thread_idx & 2) {
                s.push({thread_idx, "Test object"});
            } else {
                s.emplace(thread_idx, "Test object");
            }
        }
        ++finished;
    }

    void after() {
        /* hold thread until all finish */
        while (finished < thread_num);
        RL_ASSERT(s.size() == stack_size / 2);
    }
};

int main()
{
    rl::simulate<lockfree_race_test>();
}
