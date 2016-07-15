#ifndef HOIST_STATISTICS_H_
#define HOIST_STATISTICS_H_

#include <algorithm>
#include <cmath>
#include <iterator>
#include <map>
#include <numeric>
#include <type_traits>
#include <vector>

namespace hoist {
namespace statistics {

#define NOT_ARITHMETIC "Iterable value type must be arithmetic"

template<class InputIt>
double arithmetic_mean(InputIt first, InputIt last)
{
    using namespace std;
    static_assert(is_arithmetic<decltype(*first + *last)>::value, NOT_ARITHMETIC);

    return accumulate(next(first), last, *first) /
        static_cast<double>(distance(first, last));
}

template<class InputIt>
double median(InputIt first, InputIt last)
{
    using namespace std;
    static_assert(is_arithmetic<decltype(*first + *last)>::value, NOT_ARITHMETIC);

    auto sorted = vector<typename InputIt::value_type>(distance(first, last));
    partial_sort_copy(first, last, begin(sorted), end(sorted));

    auto range = sorted.size() - 1;
    auto it = next(begin(sorted), range / 2);
    return (static_cast<double>(*it) + *next(it, range & 1)) / 2;
}

template<class InputIt>
double standard_deviation(InputIt first, InputIt last)
{
    using namespace std;
    static_assert(is_arithmetic<decltype(*first + *last)>::value, NOT_ARITHMETIC);

    auto avg = arithmetic_mean(first, last);

    auto sorted = vector<typename InputIt::value_type>(distance(first, last));
    transform(first, last, begin(sorted),
            [avg](decltype(*first) val) { return pow(val - avg, 2); });

    return sqrt(arithmetic_mean(begin(sorted), end(sorted)));
}

#undef NOT_ARITHMETIC

}
}

#endif /* HOIST_STATISTICS_H_ */
