#include <algorithm>
#include <cassert>
#include <functional>

#include <pqalgo/sort.h>

using sortFunc = std::function<void(int[], std::size_t)>;

void unit_test(int m[], std::size_t len, const sortFunc& sf)
{
    std::size_t n = len;
    std::for_each(m, m + len, [&n](int& x){ x = int(--n); });

    sf(m, len);
    assert(std::is_sorted(m, m + len) == true);
}

int main()
{
    int m[10];
    std::size_t len = sizeof(m) / sizeof(int);

    unit_test(m, len, pqalgo::insertsort<int>);
    unit_test(m, len, pqalgo::selectsort<int>);
    unit_test(m, len, pqalgo::bubblesort<int>);

    return 0;
}
