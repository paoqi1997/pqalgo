#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "../tools.h"

namespace pits
{
    /* 冒泡排序 */
    template <typename T>
    void bubblesort(T m[], uint32_t n, char c = '<')
    {
        for (uint32_t i = 0; i < n - 1; ++i) {
            for (uint32_t j = 0; j < n - i - 1; ++j) {
                if (c == '<') {
                    if (m[j] > m[j + 1]) {
                        swap(m, j, j + 1);
                    }
                } else if (c == '>') {
                    if (m[j] < m[j + 1]) {
                        swap(m, j, j + 1);
                    }
                }
            }
        }
    }

    template <typename T>
    void bubblesort(T *pl, T *pr, char c = '<')
    {
        for (int32_t i = 0; i < (pr - pl + 1) - 1; ++i) {
            for (int32_t j = 0; j < (pr - pl + 1) - i - 1; ++j) {
                if (c == '<') {
                    if (*(pl + j) > *(pl + j + 1)) {
                        swap(pl + j, pl + j + 1);
                    }
                } else if (c == '>') {
                    if (*(pl + j) < *(pl + j + 1)) {
                        swap(pl + j, pl + j + 1);
                    }
                }
            }
        }
    }

    /* 第一个改进版本 */
    template <typename T>
    void bsort(T m[], uint32_t n, char c = '<')
    {
        uint32_t i, j, pos;

        for (i = n - 1; i > 0; ) {
            for (j = pos = 0; j < i; ++j) {
                if (c == '<') {
                    if (m[j] > m[j + 1]) {
                        pos = j; swap(m, j, j + 1);
                    }
                } else if (c == '>') {
                    if (m[j] < m[j + 1]) {
                        pos = j; swap(m, j, j + 1);
                    }
                }
            } i = pos;
        }
    }

    template <typename T>
    void bsort(T *pl, T *pr, char c = '<')
    {
        int32_t i , j, pos;

        for (i = pr - pl; i > 0; ) {
            for (j = pos = 0; j < i; ++j) {
                if (c == '<') {
                    if (*(pl + j) > *(pl + j + 1)) {
                        pos = j; swap(pl + j, pl + j + 1);
                    }
                } else if (c == '>') {
                    if (*(pl + j) < *(pl + j + 1)) {
                        pos = j; swap(pl + j, pl + j + 1);
                    }
                }
            } i = pos;
        }
    }

    /* 第二个改进版本 */
    template <typename T>
    void busort(T m[], uint32_t n, char c = '<')
    {
        uint32_t j, x, y;

        for (x = 0, y = n - 1; x < y; ) {
            for (j = x; j < y; ++j) {
                if (c == '<') {
                    if (m[j] > m[j + 1]) {
                        swap(m, j, j + 1);
                    }
                } else if (c == '>') {
                    if (m[j] < m[j + 1]) {
                        swap(m, j, j + 1);
                    }
                }
            } --y;
            for (j = y; j > x; --j) {
                if (c == '<') {
                    if (m[j - 1] > m[j]) {
                        swap(m, j, j - 1);
                    }
                } else if (c == '>') {
                    if (m[j - 1] < m[j]) {
                        swap(m, j, j - 1);
                    }
                }
            } ++x;
        }
    }

    template <typename T>
    void busort(T *pl, T *pr, char c = '<')
    {
        int32_t j, x, y;

        for (x = 0, y = pr - pl; x < y; ) {
            for (j = x; j < y; ++j) {
                if (c == '<') {
                    if (*(pl + j) > *(pl + j + 1)) {
                        swap(pl + j, pl + j + 1);
                    }
                } else if (c == '>') {
                    if (*(pl + j) < *(pl + j + 1)) {
                        swap(pl + j, pl + j + 1);
                    }
                }
            } --y;
            for (j = y; j > x; --j) {
                if (c == '<') {
                    if (*(pl + j - 1) > *(pl + j)) {
                        swap(pl + j, pl + j - 1);
                    }
                } else if (c == '>') {
                    if (*(pl + j - 1) < *(pl + j)) {
                        swap(pl + j, pl + j - 1);
                    }
                }
            } ++x;
        }
    }
}

#endif // BUBBLESORT_H
