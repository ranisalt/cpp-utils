#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "stack.h"

using hoist::lockfree::stack;
constexpr auto stack_size = 0xFFFFFF;

/* maximum number of threads guaranteed to be fed */
constexpr auto thread_num = 128;

struct Object
{
    int id;
    const char* name;
};

struct
{
    stack<Object, stack_size> lfstack;

    void before() {
        for (auto i = 0; i < stack_size / 2; ++i) {
            lfstack.emplace(i, "Test object");
        }
    }

    void after() {
        assert(lfstack.size() == stack_size / 2);
    }
} test;

void thread(int thread_idx) {
    /* hold all threads until stack is filled */
    for (auto i = 0; i < stack_size / thread_num; ++i) {
        if (thread_idx & 1) {
            test.lfstack.pop();
        } else {
            test.lfstack.emplace(thread_idx, "Test object");
        }
    }
}

int main()
{
    using namespace std::chrono;
    test.before();

    auto threads = std::vector<std::thread>{};

    auto start = steady_clock::now();
    for (auto i = 0u; i < thread_num; ++i) {
        threads.emplace_back(thread, i);
    }

    for (auto& thread: threads) {
        thread.join();
    }
    auto end = steady_clock::now();
    std::cout << duration_cast<microseconds>(end - start).count() << "us" << std::endl;

    test.after();
    return 0;
}
