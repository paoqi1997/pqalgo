#ifndef BUSORT_H
#define BUSORT_H

#include <cstdint>

#include "../modules/scalpel.h"

namespace pits
{
    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void busort(T m[], uint32_t n)
    {
        for (uint32_t x = 0, y = n - 1; x < y; )
        {
            for (uint32_t i = x; i < y; ++i)
            {
                if (m[i] > m[i + 1]) swap(m[i], m[i + 1]);
            } --y;
            for (uint32_t i = y; i > x; --i)
            {
                if (m[i - 1] > m[i]) swap(m[i], m[i - 1]);
            } ++x;
        }
    }

    /* Range: [pl, pr) */
    template <typename T>
    void busort(T *pl, T *pr)
    {
        for (int32_t x = 0, y = pr - pl - 1; x < y; )
        {
            for (int32_t i = x; i < y; ++i)
            {
                if (*(pl + i) > *(pl + i + 1)) swap(*(pl + i), *(pl + i + 1));
            } --y;
            for (int32_t i = y; i > x; --i)
            {
                if (*(pl + i - 1) > *(pl + i)) swap(*(pl + i), *(pl + i - 1));
            } ++x;
        }
    }

    /* Range: [first, last) */
    template <typename Iterator>
    void busort(Iterator first, Iterator last)
    {
        for (ptrdiff_t x = 0, y = last - first - 1; x < y; )
        {
            for (ptrdiff_t i = x; i < y; ++i)
            {
                if (*(first + i) > *(first + i + 1)) swap(*(first + i), *(first + i + 1));
            } --y;
            for (ptrdiff_t i = y; i > x; --i)
            {
                if (*(first + i - 1) > *(first + i)) swap(*(first + i), *(first + i - 1));
            } ++x;
        }
    }
}

#endif // BUSORT_H
