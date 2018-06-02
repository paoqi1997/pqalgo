#ifndef SELECTSORT_H
#define SELECTSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /**
     * Range: m[0] - m[n - 1]
     */
    template <typename T>
    void selectsort(T m[], uint32_t n)
    {
        for (uint32_t i = 0; i < n; ++i)
        {
            auto pos = i;

            auto tm = m[i], ti = m[i];

            for (uint32_t j = i + 1; j < n; ++j)
            {
                if (tm > m[j])
                {
                    tm = m[j]; pos = j;
                }
            } m[i] = tm; m[pos] = ti;
        }
    }

    /**
     * Range: [pl, pr)
     */
    template <typename T>
    void selectsort(T *pl, T *pr)
    {
        for (int32_t i = 0; i < pr - pl; ++i)
        {
            auto pos = i;

            auto tm = *(pl + i), ti = *(pl + i);

            for (int32_t j = i + 1; j < pr - pl; ++j)
            {
                if (tm > *(pl + j))
                {
                    tm = *(pl + j); pos = j;
                }
            } *(pl + i) = tm; *(pl + pos) = ti;
        }
    }

    /**
     * Range: [first, last)
     */
    template <typename RandomIt>
    void selectsort(RandomIt first, RandomIt last)
    {
        for (ptrdiff_t i = 0; i < last - first; ++i)
        {
            auto pos = i;

            auto tm = *(first + i), ti = *(first + i);

            for (ptrdiff_t j = i + 1; j < last - first; ++j)
            {
                if (tm > *(first + j))
                {
                    tm = *(first + j); pos = j;
                }
            } *(first + i) = tm; *(first + pos) = ti;
        }
    }
}

#endif // SELECTSORT_H
