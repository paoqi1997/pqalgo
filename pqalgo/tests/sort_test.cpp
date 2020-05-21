#include <algorithm>
#include <cassert>
#include <iterator>

#include <pqalgo/sort.h>

int main()
{
    int m[10];
    std::size_t len = sizeof(m) / sizeof(int);

    std::size_t n = len;
    std::for_each(std::begin(m), std::end(m), [&n](int& x){ x = int(--n); });

    n = len;
    pqalgo::bubblesort(m, n);

    bool sorted = std::is_sorted(std::begin(m), std::end(m));
    assert(sorted == true);

    return 0;
}
