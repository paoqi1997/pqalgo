#ifndef BUBBLESORT_H
#define BUBBLESORT_H

namespace pits
{
    using  int32_t = int;
    using uint32_t = unsigned int;

    template <typename T>
    void bubblesort(T m[], uint32_t n, char c = '<')
    {
        T temp; uint32_t i, j;

        for (i = 0; i < n - 1; ++i) {
            for (j = 0; j < n - i - 1; ++j) {
                if (c == '<') {
                    if (m[j] > m[j + 1]) {
                        temp = m[j];
                        m[j] = m[j + 1];
                        m[j + 1] = temp;
                    }
                } else if (c == '>') {
                    if (m[j] < m[j + 1]) {
                        temp = m[j];
                        m[j] = m[j + 1];
                        m[j + 1] = temp;
                    }
                }
            }
        }
    }

    template <typename T>
    void bubblesort(T *pl, T *pr, char c = '<')
    {
        T *pt = new T; int32_t i, j;

        for (i = 0; i < (pr - pl + 1) - 1; ++i) {
            for (j = 0; j < (pr - pl + 1) - i - 1; ++j) {
                if (c == '<') {
                    if (*(pl + j) > *(pl + j + 1)) {
                        *pt = *(pl + j);
                        *(pl + j) = *(pl + j + 1);
                        *(pl + j + 1) = *pt;
                    }
                } else if (c == '>') {
                    if (*(pl + j) < *(pl + j + 1)) {
                        *pt = *(pl + j);
                        *(pl + j) = *(pl + j + 1);
                        *(pl + j + 1) = *pt;
                    }
                }
            }
        } delete pt;
    }
}

#endif // BUBBLESORT_H
