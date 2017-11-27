#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "../tools.h"

namespace pits
{
    /* 希尔排序 */
    template <typename T>
    void shellsort(T m[], int32_t n, char c = '<')
    {
        int32_t i, j, gap;

        for (gap = n / 2; gap > 0; gap /= 2) {
            for (i = gap; i < n; ++i) {
                if (c == '<') {
                    for (j = i - gap;
                         j >= 0 && m[j] > m[j + gap]; j -= gap) {
                        swap(m, j, j + gap);
                    }
                } else if (c == '>') {
                    for (j = i - gap;
                         j >= 0 && m[j] < m[j + gap]; j -= gap) {
                        swap(m, j, j + gap);
                    }
                }
            }
        }
    }

    template <typename T>
    void shellsort(T *pl, T *pr, char c = '<')
    {
        int32_t i, j, gap;

        for (gap = (pr - pl + 1) / 2; gap > 0; gap /= 2) {
            for (i = gap; i < (pr - pl + 1); ++i) {
                if (c == '<') {
                    for (j = i - gap;
                         j >= 0 && *(pl + j) > *(pl + j + gap); j -= gap) {
                        swap(pl + j, pl + j + gap);
                    }
                } else if (c == '>') {
                    for (j = i - gap;
                         j >= 0 && *(pl + j) < *(pl + j + gap); j -= gap) {
                        swap(pl + j, pl + j + gap);
                    }
                }
            }
        }
    }
}

#endif // SHELLSORT_H
