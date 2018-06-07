#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /**
     * Range: m[l] - m[r]
     */
    template <typename T>
    void quicksort(T m[], int32_t l, int32_t r)
    {
        if (l < r)
        {
            auto tm = m[l];

            int32_t i = l, j = r;

            while (i < j)
            {
                while (i < j && m[j] > tm)
                {
                    --j;
                }
                if (i < j)
                {
                    std::swap(m[i], m[j]);
                }
                while (i < j && m[i] < tm)
                {
                    ++i;
                }
                if (i < j)
                {
                    std::swap(m[i], m[j]);
                }
            } quicksort(m, l, i - 1); quicksort(m, i + 1, r);
        }
    }

    /**
     * Range: [pl, pr]
     */
    template <typename T>
    void quicksort(T *pl, T *pr)
    {
        if (pl < pr)
        {
            auto tm = *pl;

            int32_t i = 0, j = pr - pl;

            while (i < j)
            {
                while (i < j && *(pl + j) > tm)
                {
                    --j;
                }
                if (i < j)
                {
                    std::swap(*(pl + i), *(pl + j));
                }
                while (i < j && *(pl + i) < tm)
                {
                    ++i;
                }
                if (i < j)
                {
                    std::swap(*(pl + i), *(pl + j));
                }
            } quicksort(pl, pl + i - 1); quicksort(pl + i + 1, pr);
        }
    }

    /**
     * Range: [first, last]
     */
    template <typename RandomIt>
    void quicksort(RandomIt first, RandomIt last)
    {
        if (first < last)
        {
            auto tm = *first;

            ptrdiff_t i = 0, j = last - first;

            while (i < j)
            {
                while (i < j && *(first + j) > tm)
                {
                    --j;
                }
                if (i < j)
                {
                    std::swap(*(first + i), *(first + j));
                }
                while (i < j && *(first + i) < tm)
                {
                    ++i;
                }
                if (i < j)
                {
                    std::swap(*(first + i), *(first + j));
                }
            } quicksort(first, first + i - 1); quicksort(first + i + 1, last);
        }
    }
}

#endif // QUICKSORT_H
