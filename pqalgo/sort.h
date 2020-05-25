#ifndef PQALGO_SORT_H
#define PQALGO_SORT_H

#include <cstddef>
#include <utility>

namespace pqalgo
{

template <typename T>
void selectsort(T m[], std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        std::size_t idx = i;
        for (std::size_t j = i + 1; j < n; ++j)
        {
            if (m[idx] > m[j]) {
                idx = j;
            }
        }
        std::swap(m[i], m[idx]);
    }
}

template <typename T>
void bubblesort(T m[], std::size_t n)
{
    for (std::size_t i = 0; i < n - 1; ++i)
    {
        for (std::size_t j = 0; j < n - i - 1; ++j)
        {
            if (m[j] > m[j + 1]) {
                std::swap(m[j], m[j + 1]);
            }
        }
    }
}

} // namespace pqalgo

#endif // PQALGO_SORT_H