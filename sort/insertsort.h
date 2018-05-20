#ifndef INSERTSORT_H
#define INSERTSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void insertsort(T m[], uint32_t n)
    {
        uint32_t i, j;

        for (i = 1; i < n; ++i)
        {
            if (m[i - 1] > m[i])
            {
                auto tm = m[i];

                for (j = i; j > 0 && m[j - 1] > tm; --j)
                {
                    m[j] = m[j - 1];
                }
                
                m[j] = tm;
            }
        }
    }

    /* Range: [pl, pr) */
    template <typename T>
    void insertsort(T *pl, T *pr)
    {
        int32_t i, j;

        for (i = 1; i < pr - pl; ++i)
        {
            if (*(pl + i - 1) > *(pl + i))
            {
                auto tm = *(pl + i);

                for (j = i; j > 0 && *(pl + j - 1) > tm; --j)
                {
                    *(pl + j) = *(pl + j - 1);
                }
                
                *(pl + j) = tm;
            }
        }
    }

    /* Range: [first, last) */
    template <typename RandomIt>
    void insertsort(RandomIt first, RandomIt last)
    {
        ptrdiff_t i, j;

        for (i = 1; i < last - first; ++i)
        {
            if (*(first + i - 1) > *(first + i))
            {
                auto tm = *(first + i);

                for (j = i; j > 0 && *(first + j - 1) > tm; --j)
                {
                    *(first + j) = *(first + j - 1);
                }
                
                *(first + j) = tm;
            }
        }
    }
}

#endif // INSERTSORT_H
