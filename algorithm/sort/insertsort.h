#ifndef INSERTSORT_H
#define INSERTSORT_H

#include "../tools.h"

namespace pits
{
    template <typename T>
    void insertsort(T m[], uint32_t n, char c = '<')
    {
        T temp; uint32_t i, j;

        for (i = 1; i < n; ++i) {
            if (c == '<') {
                if (m[i - 1] > m[i]) { temp = m[i];
                    for (j = i; j > 0 && m[j - 1] > temp; --j) {
                        m[j] = m[j - 1];
                    } m[j] = temp;
                }
            } else if (c == '>') {
                if (m[i - 1] < m[i]) { temp = m[i];
                    for (j = i; j > 0 && m[j - 1] < temp; --j) {
                        m[j] = m[j - 1];
                    } m[j] = temp;
                }
            }
        }
    }

    template <typename T>
    void insertsort(T *pl, T *pr, char c = '<')
    {
        T *pt = new T; int32_t i, j;

        for (i = 1; i < (pr - pl + 1); ++i) {
            if (c == '<') {
                if (*(pl + i - 1) > *(pl + i)) { *pt = *(pl + i);
                    for (j = i; j > 0 && *(pl + j - 1) > *pt; --j) {
                        *(pl + j) = *(pl + j - 1);
                    } *(pl + j) = *pt;
                }
            } else if (c == '>') {
                if (*(pl + i - 1) < *(pl + i)) { *pt = *(pl + i);
                    for (j = i; j > 0 && *(pl + j - 1) < *pt; --j) {
                        *(pl + j) = *(pl + j - 1);
                    } *(pl + j) = *pt;
                }
            }
        } delete pt;
    }
}

#endif // INSERTSORT_H
