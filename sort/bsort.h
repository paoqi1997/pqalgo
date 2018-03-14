#ifndef BSORT_H
#define BSORT_H

#include <cstdint>

#include "../modules/scalpel.h"

namespace pits
{
    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void bsort(T m[], uint32_t n)
    {
        uint32_t i, j, pos;

        for (i = n - 1; i > 0; )
        {
            for (j = pos = 0; j < i; ++j)
            {
                if (m[j] > m[j + 1])
                {
                    pos = j; swap(m[j], m[j + 1]);
                }
            } i = pos;
        }
    }

    /* Range: [pl, pr) */
    template <typename T>
    void bsort(T *pl, T *pr)
    {
        int32_t i, j, pos;

        for (i = pr - pl - 1; i > 0; )
        {
            for (j = pos = 0; j < i; ++j)
            {
                if (*(pl + j) > *(pl + j + 1))
                {
                    pos = j; swap(*(pl + j), *(pl + j + 1));
                }
            } i = pos;
        }
    }

    /* Range: [first, last) */
    template <typename Iterator>
    void bsort(Iterator first, Iterator last)
    {
        ptrdiff_t i, j, pos;

        for (i = last - first - 1; i > 0; )
        {
            for (j = pos = 0; j < i; ++j)
            {
                if (*(first + j) > *(first + j + 1))
                {
                    pos = j; swap(*(first + j), *(first + j + 1));
                }
            } i = pos;
        }
    }
}

#endif // BSORT_H
