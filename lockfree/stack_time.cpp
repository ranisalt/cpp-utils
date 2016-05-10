#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "stack.h"

using namespace hoist::lockfree;
constexpr auto stack_size = 0xFFFFFF;

/* maximum number of threads guaranteed to be fed */
constexpr auto thread_num = 128;

struct Object
{
    int id;

    Object(int id): id{id} {}
};

struct
{
    stack<Object> s;
    std::deque<Object> d;

    void before() {
        for (auto i = 0; i < stack_size / 2; ++i) {
            s.emplace(i);
            d.emplace_back(i);
        }
    }

    void after() {}
} test;

void lf_worker_thread(int thread_idx) {
    Object o{thread_idx};
    /* hold all threads until stack is filled */
    for (auto i = 0; i < stack_size / thread_num; ++i) {
        if (thread_idx & 1) {
            test.s.pop();
        } else {
            test.s.push(o);
        }
    }
}

static std::mutex ex;
void l_worker_thread(int thread_idx) {
    Object o{thread_idx};
    /* hold all threads until stack is filled */
    for (auto i = 0; i < stack_size / thread_num; ++i) {
        if (thread_idx & 1) {
            std::lock_guard<std::mutex> lock{ex};
            test.d.pop_back();
        } else {
            std::lock_guard<std::mutex> lock{ex};
            test.d.push_back(o);
        }
    }
}

int main()
{
    using namespace std::chrono;
    test.before();

    auto threads = std::vector<std::thread>{};

    {
        auto start = steady_clock::now();
        for (auto i = 0u; i < thread_num; ++i) {
            threads.emplace_back(lf_worker_thread, i);
        }

        for (auto& thread: threads) {
            thread.join();
        }
        auto end = steady_clock::now();
        std::cout << duration_cast<microseconds>(end - start).count() << "us" << std::endl;
    }

    threads.clear();

    {
        auto start = steady_clock::now();
        for (auto i = 0u; i < thread_num; ++i) {
            threads.emplace_back(l_worker_thread, i);
        }

        for (auto& thread: threads) {
            thread.join();
        }
        auto end = steady_clock::now();
        std::cout << duration_cast<microseconds>(end - start).count() << "us" << std::endl;
    }

    test.after();
    return 0;
}
