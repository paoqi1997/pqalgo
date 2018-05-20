#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdint>
#include <cstddef>
#include <utility>

namespace pits
{
    template <typename T>
    void sift(T m[], int32_t root, int32_t n)
    {
        auto tm = m[root], leaf = 2 * root + 1;   /* 取得原始根节点的值及左叶子节点的索引 */

        while (leaf < n)                          /* 索引未越界 */
        {
            if (leaf + 1 < n &&
                    m[leaf] < m[leaf + 1])        /* 左叶子节点的值小于右叶子节点的值 */
            {
                ++leaf;
            }
            if (tm < m[leaf])                     /* 原始根节点的值小于左叶子节点的值 */
            {
                m[root] = m[leaf];

                root = leaf; leaf = 2 * root + 1; /* 调整根节点及左叶子节点 */
            }
            else
            {
                break;
            }
        } m[root] = tm;                           /* 将原始根节点的值传递给调整后的根节点 */
    }

    /* Range: m[0] - m[n - 1] */
    template <typename T>
    void heapsort(T m[], int32_t n)
    {
        for (int32_t i = n / 2 - 1; i >= 0; --i)  /* 建立堆 */
        {
            sift(m, i, n);
        }
        for (int32_t j = 1; j < n; ++j)           /* 交换根节点与调整前最后一个叶子节点的值 */
        {
            std::swap(m[0], m[n - j]); sift(m, 0, n - j);
        }
    }

    template <typename T>
    void adjust(T *p, int32_t root, int32_t n)
    {
        auto tm = *(p + root), leaf = 2 * root + 1;

        while (leaf < n)
        {
            if (leaf + 1 < n && *(p + leaf) < *(p + leaf + 1))
            {
                ++leaf;
            }
            if (tm < *(p + leaf))
            {
                *(p + root) = *(p + leaf); root = leaf; leaf = 2 * root + 1;
            }
            else
            {
                break;
            }
        } *(p + root) = tm;
    }

    /* Range: [pl, pr) */
    template <typename T>
    void heapsort(T *pl, T *pr)
    {
        for (int32_t i = (pr - pl) / 2 - 1; i >= 0; --i)
        {
            adjust(pl, i, pr - pl);
        }
        for (int32_t j = 1; j < pr - pl; ++j)
        {
            std::swap(*pl, *(pl + (pr - pl) - j)); adjust(pl, 0, pr - pl - j);
        }
    }
}

#endif // HEAPSORT_H
