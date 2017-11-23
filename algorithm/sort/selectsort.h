#ifndef SELECTSORT_H
#define SELECTSORT_H

#include "../tools.h"

namespace pits
{
    /* 选择排序 */
    template <typename T>
    void selectsort(T m[], uint32_t n, char c = '<')
    {
        T tm, te; uint32_t i, j, pos;

        for (i = 0; i < n; ++i) {
            tm = te = m[i]; pos = i;
            for (j = i + 1; j < n; ++j) {
                if (c == '<') {
                    if (m[j] < tm) {
                        tm = m[j]; pos = j;
                    }
                } else if (c == '>') {
                    if (m[j] > tm) {
                        tm = m[j]; pos = j;
                    }
                }
            } m[i] = tm; m[pos] = te;
        }
    }

    template <typename T>
    void selectsort(T *pl, T *pr, char c = '<')
    {
        int32_t i, j, pos;

        T *tm = new T, *te = new T;

        for (i = 0; i < (pr - pl + 1); ++i) {
            *tm = *te = *(pl + i); pos = i;
            for (j = i + 1; j < (pr - pl + 1); ++j) {
                if (c == '<') {
                    if (*(pl + j) < *tm) {
                        *tm = *(pl + j); pos = j;
                    }
                } else if (c == '>') {
                    if (*(pl + j) > *tm) {
                        *tm = *(pl + j); pos = j;
                    }
                }
            } *(pl + i) = *tm; *(pl + pos) = *te;
        } delete tm; delete te;
    }

    /* 二元选择排序 */
    template <typename T>
    void ssort(T m[], uint32_t n, char c = '<')
    {
        uint32_t i, j, tmin, tmax;

        for (i = 0; i < n / 2; ++i) {
            tmin = tmax = i;
            for (j = i; j < n - i; ++j) {
                if (m[j] < m[tmin]) {
                    tmin = j;
                }
                if (m[j] > m[tmax]) {
                    tmax = j;
                }
            }
            if (c == '<') {
                swap(m, i, tmin);
                if (i == tmax)
                    swap(m, n - i - 1, tmin);
                else
                    swap(m, n - i - 1, tmax);
            } else if (c == '>') {
                swap(m, i, tmax);
                if (i == tmin)
                    swap(m, n - i - 1, tmax);
                else
                    swap(m, n - i - 1, tmin);
            }
        }
    }

    template <typename T>
    void ssort(T *pl, T *pr, char c = '<')
    {
        int32_t i, j, tmin, tmax;

        for (i = 0; i < (pr - pl + 1) / 2; ++i) {
            tmin = tmax = i;
            for (j = i; j < (pr - pl + 1) - i; ++j) {
                if (*(pl + j) < *(pl + tmin)) {
                    tmin = j;
                }
                if (*(pl + j) > *(pl + tmax)) {
                    tmax = j;
                }
            }
            if (c == '<') {
                swap(pl + i, pl + tmin);
                if (i == tmax)
                    swap(pl + (pr - pl) - i, pl + tmin);
                else
                    swap(pl + (pr - pl) - i, pl + tmax);
            } else if (c == '>') {
                swap(pl + i, pl + tmax);
                if (i == tmin)
                    swap(pl + (pr - pl) - i, pl + tmax);
                else
                    swap(pl + (pr - pl) - i, pl + tmin);
            }
        }
    }
}

#endif // SELECTSORT_H
