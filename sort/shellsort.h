#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void shellsort(T m[], int32_t n)
    {
        int32_t i, j, gap;

        for (gap = n / 2; gap > 0; gap /= 2)
        {
            for (i = gap; i < n; ++i)
            {
                for (j = i - gap; j >= 0 && m[j] > m[j + gap]; j -= gap)
                {
                    std::swap(m[j], m[j + gap]);
                }
            }
        }
    }

    /* Range: [pl, pr) */
    template <typename T>
    void shellsort(T *pl, T *pr)
    {
        int32_t i, j, gap;

        for (gap = (pr - pl) / 2; gap > 0; gap /= 2)
        {
            for (i = gap; i < pr - pl; ++i)
            {
                for (j = i - gap; j >= 0 && *(pl + j) > *(pl + j + gap); j -= gap)
                {
                    std::swap(*(pl + j), *(pl + j + gap));
                }
            }
        }
    }

    /* Range: [first, last) */
    template <typename RandomIt>
    void shellsort(RandomIt first, RandomIt last)
    {
        ptrdiff_t i, j, gap;

        for (gap = (last - first) / 2; gap > 0; gap /= 2)
        {
            for (i = gap; i < last - first; ++i)
            {
                for (j = i - gap; j >= 0 && *(first + j) > *(first + j + gap); j -= gap)
                {
                    std::swap(*(first + j), *(first + j + gap));
                }
            }
        }
    }
}

#endif // SHELLSORT_H
