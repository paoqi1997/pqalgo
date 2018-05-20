#ifndef MERGESORT_H
#define MERGESORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    template <typename T>
    void merge(T m1[], T m2[], int32_t low, int32_t middle, int32_t high)
    {
        int32_t i = low, j = middle + 1; /* 取得左子表及右子表的索引 */

        while (i <= middle && j <= high) /* 子表索引未越界 */
        {
            if (m1[i] < m1[j])
                m2[low++] = m1[i++];     /* 移动左子表元素到m2中 */
            else
                m2[low++] = m1[j++];     /* 移动右子表元素到m2中 */
        }
        while (i <= middle)
            m2[low++] = m1[i++];         /* 移动左子表剩余元素到m2中 */

        while (j <= high)
            m2[low++] = m1[j++];         /* 移动右子表剩余元素到m2中 */
    }

    template <typename T>
    void pass(T m1[], T m2[], int32_t len, int32_t n)
    {
        int32_t pos = 0;                   /* 为m1建立索引 */

        while (pos + 2 * len - 1 <= n - 1) /* 可在m1中建立两个子表 */
        {
            merge(m1, m2, pos, pos + len - 1, pos + 2 * len - 1);

            pos += 2 * len;
        }
        if (pos + len - 1 <= n - 1)        /* 还可在m1中建立子表 */
        {
            merge(m1, m2, pos, pos + len - 1, n - 1);
        }
        else                               /* 无法在m1中建立子表 */
        {
            for (int32_t i = pos; i < n; ++i)
            {
                m2[i] = m1[i];             /* 移动m1剩余元素到m2中 */
            }
        }
    }

    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void mergesort(T m[], int32_t n)
    {
        T w[n]; /* 辅助数组w */

        for (int32_t len = 1; len < n; )
        {
            pass(m, w, len, n); len *= 2; /* 将m分割为长度为len的子表并传递到w中 */

            pass(w, m, len, n); len *= 2; /* 将w分割为长度为len的子表并传递到m中 */
        }
    }

    template <typename T>
    void combine(T *p, T *q, int32_t low, int32_t middle, int32_t high)
    {
        int32_t i = low, j = middle + 1;

        while (i <= middle && j <= high)
        {
            if (*(p + i) < *(p + j))
            {
                *(q + low) = *(p + i); ++low, ++i;
            }
            else
            {
                *(q + low) = *(p + j); ++low, ++j;
            }
        }
        while (i <= middle)
        {
            *(q + low) = *(p + i); ++low, ++i;
        }
        while (j <= high)
        {
            *(q + low) = *(p + j); ++low, ++j;
        }
    }

    template <typename T>
    void transmit(T *p, T *q, int32_t len, int32_t n)
    {
        int32_t pos = 0;

        while (pos + 2 * len - 1 <= n - 1)
        {
            combine(p, q, pos, pos + len - 1, pos + 2 * len - 1);

            pos += 2 * len;
        }
        if (pos + len - 1 <= n - 1)
        {
            combine(p, q, pos, pos + len - 1, n - 1);
        }
        else
        {
            for (int32_t i = pos; i < n; ++i)
            {
                *(q + i) = *(p + i);
            }
        }
    }

    /* Range: [pl, pr) */
    template <typename T>
    void mergesort(T *pl, T *pr)
    {
        T m[pr - pl];

        for (int32_t len = 1; len < pr - pl; )
        {
            transmit(pl, m, len, pr - pl); len *= 2;

            transmit(m, pl, len, pr - pl); len *= 2;
        }
    }
}

#endif // MERGESORT_H
