#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /**
     * Range: m[0] - m[n - 1]
     */
    template <typename T>
    void bubblesort(T m[], uint32_t n)
    {
        for (uint32_t i = 0; i < n - 1; ++i)
        {
            for (uint32_t j = 0; j < n - i - 1; ++j)
            {
                if (m[j] > m[j + 1]) std::swap(m[j], m[j + 1]);
            }
        }
    }

    /**
     * Range: [pl, pr)
     */
    template <typename T>
    void bubblesort(T *pl, T *pr)
    {
        for (int32_t i = 0; i < pr - pl - 1; ++i)
        {
            for (int32_t j = 0; j < pr - pl - i - 1; ++j)
            {
                if (*(pl + j) > *(pl + j + 1)) std::swap(*(pl + j), *(pl + j + 1));
            }
        }
    }

    /**
     * Range: [first, last)
     */
    template <typename RandomIt>
    void bubblesort(RandomIt first, RandomIt last)
    {
        for (ptrdiff_t i = 0; i < last - first - 1; ++i)
        {
            for (ptrdiff_t j = 0; j < last - first - i - 1; ++j)
            {
                if (*(first + j) > *(first + j + 1)) std::swap(*(first + j), *(first + j + 1));
            }
        }
    }
}

#endif // BUBBLESORT_H
