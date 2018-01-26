#ifndef SCALPEL_H
#define SCALPEL_H

#include <cstddef>

namespace pits
{
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp; temp = a; a = b; b = temp;
    }

    template <typename T, size_t N>
    void swap(T(&a)[N], T(&b)[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            T temp; temp = a[i]; a[i] = b[i]; b[i] = temp;
        }
    }
}

#endif // SCALPEL_H
