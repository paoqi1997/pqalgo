#include <algorithm>
#include <cassert>
#include <iostream>

#include <pqalgo/qsort.h>
#include <pqalgo/sort.h>

#define UNITTEST(m, len, sortfunc)                            \
do {                                                          \
    std::size_t n = len;                                      \
    std::for_each(m, m + len, [&n](int& x){ x = int(--n); }); \
                                                              \
    sortfunc(m, len);                                         \
    assert(std::is_sorted(m, m + len));                       \
} while (0)

using std::cout;
using std::endl;

int main()
{
    int m[10];
    std::size_t len = sizeof(m) / sizeof(int);

    UNITTEST(m, len, pqalgo::insertsort);
    UNITTEST(m, len, pqalgo::shellsort);
    UNITTEST(m, len, pqalgo::selectsort);
    UNITTEST(m, len, pqalgo::heapsort);
    UNITTEST(m, len, pqalgo::bubblesort);
    UNITTEST(m, len, pqalgo::quicksort);
    UNITTEST(m, len, pqalgo::quicksort_nr);
    UNITTEST(m, len, pqalgo::quicksort_v2);
    UNITTEST(m, len, pqalgo::quicksort_v3);
    UNITTEST(m, len, pqalgo::mergesort);
    UNITTEST(m, len, pqalgo::mergesort_r);
    UNITTEST(m, len, pqalgo::radixsort);

    cout << "ok." << endl;

    return 0;
}
