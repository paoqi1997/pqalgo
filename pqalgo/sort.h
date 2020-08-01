#ifndef PQALGO_SORT_H
#define PQALGO_SORT_H

#include <cstddef>
#include <utility>

namespace pqalgo
{

template <typename T>
void insertsort(T m[], std::size_t n)
{
    for (std::size_t i = 1; i < n; ++i)
    {
        T tmpVal = m[i];
        std::size_t j = i;
        while (j > 0 && m[j - 1] > tmpVal)
        {
            m[j] = m[j - 1];
            --j;
        }
        m[j] = tmpVal;
    }
}

template <typename T>
void shellsort(T m[], std::size_t n)
{
    for (std::size_t gap = n / 2; gap > 0; gap /= 2)
    {
        for (std::size_t i = gap; i < n; ++i)
        {
            T tmpVal = m[i];
            std::size_t j = i;
            while (j > 0 && m[j - gap] > tmpVal)
            {
                m[j] = m[j - gap];
                j -= gap;
            }
            m[j] = tmpVal;
        }
    }
}

template <typename T>
void selectsort(T m[], std::size_t n)
{
    for (std::size_t i = 0; i < n - 1; ++i)
    {
        std::size_t minIdx = i;
        for (std::size_t j = i + 1; j < n; ++j)
        {
            if (m[minIdx] > m[j]) {
                minIdx = j;
            }
        }
        std::swap(m[i], m[minIdx]);
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
