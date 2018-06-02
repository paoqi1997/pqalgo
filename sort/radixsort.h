#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    template <typename T>
    int32_t maxbit(T m[], int32_t n)
    {
        int32_t digit = 1, contrast = 10; /* 定义位数digit */

        for (int32_t i = 0; i < n; ++i)
        {
            while (m[i] >= contrast)      /* 元素大于digit位数 */
            {
                contrast *= 10; digit += 1;
            }
        } return digit;
    }

    /**
     * Range: m[0] - m[n - 1]
     */
    template <typename T>
    void radixsort(T m[], int32_t n)
    {
        T bucket[n];

        int32_t count[10];

        int32_t i, j, k, radix = 1;

        for (i = 1; i <= maxbit(m, n); ++i)
        {
            for (j = 0; j < 10; ++j)
            {
                count[j] = 0;             /* 重置计数器 */
            }

            for (j = 0; j < n; ++j)
            {
                k = (m[j] / radix) % 10;  /* 取得每个元素目标位的值 */

                ++count[k];               /* 计数器的相应数值+1 */
            }

            for (j = 1; j < 10; ++j)
            {
                count[j] += count[j - 1]; /* 取得第j个桶的右边界索引 */
            }

            /* Example: count[10] <-> 3 6 8 9 9 9 9 9 9 9 */

            /* 第1个桶为bucket[0] - bucket[2]...第2个桶为bucket[3] - bucket[5]...依此类推 */

            for (j = n - 1; j >= 0; --j)
            {
                k = (m[j] / radix) % 10;     /* 取得每个元素目标位的值 */

                bucket[count[k] - 1] = m[j]; /* 将元素放入对应的桶中 */

                --count[k];                  /* 计数器的相应数值-1 */
            }

            for (j = 0; j < n; ++j)
            {
                m[j] = bucket[j];            /* 将桶倒入m[j]中 */
            }

            radix *= 10;
        }
    }

    template <typename T>
    int32_t digits(T *p, int32_t n)
    {
        int32_t digit = 1, contrast = 10;

        for (int32_t i = 0; i < n; ++i)
        {
            while (*(p + i) >= contrast)
            {
                contrast *= 10; digit += 1;
            }
        } return digit;
    }

    /**
     * Range: [pl, pr)
     */
    template <typename T>
    void radixsort(T *pl, T *pr)
    {
        T bucket[pr - pl];

        int32_t count[10];

        int32_t i, j, k, radix = 1;

        for (i = 1; i <= digits(pl, pr - pl); ++i)
        {
            for (j = 0; j < 10; ++j)
            {
                count[j] = 0;
            }

            for (j = 0; j < pr - pl; ++j)
            {
                k = (*(pl + j) / radix) % 10;

                ++count[k];
            }

            for (j = 1; j < 10; ++j)
            {
                count[j] += count[j - 1];
            }

            for (j = pr - pl - 1; j >= 0; --j)
            {
                k = (*(pl + j) / radix) % 10;

                bucket[count[k] - 1] = *(pl + j);

                --count[k];
            }

            for (j = 0; j < pr - pl; ++j)
            {
                *(pl + j) = bucket[j];
            }

            radix *= 10;
        }
    }

    template <typename RandomIt>
    int32_t places(RandomIt it, int32_t n)
    {
        int32_t digit = 1, contrast = 10;

        for (int32_t i = 0; i < n; ++i)
        {
            while (*(it + i) >= contrast)
            {
                contrast *= 10; digit += 1;
            }
        } return digit;
    }

    /**
     * Range: [first, last)
     */
    template <typename RandomIt>
    void radixsort(RandomIt first, RandomIt last)
    {
        decltype(*first) bucket[last - first];

        int32_t count[10];

        int32_t i, j, k, radix = 1;

        for (i = 1; i <= places(first, last - first); ++i)
        {
            for (j = 0; j < 10; ++j)
            {
                count[j] = 0;
            }

            for (j = 0; j < last - first; ++j)
            {
                k = (*(first + j) / radix) % 10;

                ++count[k];
            }

            for (j = 1; j < 10; ++j)
            {
                count[j] += count[j - 1];
            }

            for (j = last - first - 1; j >= 0; --j)
            {
                k = (*(first + j) / radix) % 10;

                bucket[count[k] - 1] = *(first + j);

                --count[k];
            }

            for (j = 0; j < last - first; ++j)
            {
                *(first + j) = bucket[j];
            }

            radix *= 10;
        }
    }
}

#endif // RADIXSORT_H
