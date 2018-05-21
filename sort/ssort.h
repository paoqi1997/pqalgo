#ifndef SSORT_H
#define SSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /**
     * Range: m[0] - m[n - 1]
     */
    template <typename T>
    void ssort(T m[], uint32_t n)
    {
        for (uint32_t i = 0; i < n / 2; ++i)
        {
            auto tmin = i, tmax = i;

            for (uint32_t j = i; j < n - i; ++j)
            {
                if (m[j] < m[tmin])
                {
                    tmin = j;
                }
                if (m[j] > m[tmax])
                {
                    tmax = j;
                }
            } std::swap(m[i], m[tmin]);

            if (i == tmax)
                std::swap(m[n - i - 1], m[tmin]);
            else
                std::swap(m[n - i - 1], m[tmax]);
        }
    }

    /**
     * Range: [pl, pr)
     */
    template <typename T>
    void ssort(T *pl, T *pr)
    {
        for (int32_t i = 0; i < (pr - pl) / 2; ++i)
        {
            auto tmin = i, tmax = i;

            for (int32_t j = i; j < pr - pl - i; ++j)
            {
                if (*(pl + j) < *(pl + tmin))
                {
                    tmin = j;
                }
                if (*(pl + j) > *(pl + tmax))
                {
                    tmax = j;
                }
            } std::swap(*(pl + i), *(pl + tmin));

            if (i == tmax)
                std::swap(*(pl + (pr - pl) - i - 1), *(pl + tmin));
            else
                std::swap(*(pl + (pr - pl) - i - 1), *(pl + tmax));
        }
    }

    /**
     * Range: [first, last)
     */
    template <typename RandomIt>
    void ssort(RandomIt first, RandomIt last)
    {
        for (ptrdiff_t i = 0; i < (last - first) / 2; ++i)
        {
            auto tmin = i, tmax = i;

            for (ptrdiff_t j = i; j < last - first - i; ++j)
            {
                if (*(first + j) < *(first + tmin))
                {
                    tmin = j;
                }
                if (*(first + j) > *(first + tmax))
                {
                    tmax = j;
                }
            } std::swap(*(first + i), *(first + tmin));

            if (i == tmax)
                std::swap(*(first + (last - first) - i - 1), *(first + tmin));
            else
                std::swap(*(first + (last - first) - i - 1), *(first + tmax));
        }
    }
}

#endif // SSORT_H
