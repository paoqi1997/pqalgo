#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "../tools.h"

namespace pits
{
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
}

#endif // BUBBLESORT_H
