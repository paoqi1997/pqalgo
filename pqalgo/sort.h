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
void __heapsort(T m[], std::size_t rootIndex, std::size_t n)
{
    T rootVal = m[rootIndex];
    std::size_t leafIndex = rootIndex * 2 + 1;
    while (leafIndex < n)
    {
        if (leafIndex + 1 < n && m[leafIndex] < m[leafIndex + 1]) {
            ++leafIndex;
        }
        if (rootVal < m[leafIndex]) {
            m[rootIndex] = m[leafIndex];
            rootIndex = leafIndex, leafIndex = rootIndex * 2 + 1;
        } else {
            break;
        }
    }
    m[rootIndex] = rootVal;
}

template <typename T>
void heapsort(T m[], std::size_t n)
{
    for (int i = n / 2 - 1; i >= 0; --i) {
        __heapsort(m, i, n);
    }
    for (std::size_t i = 1; i < n; ++i)
    {
        std::swap(m[0], m[n - i]);
        __heapsort(m, 0, n - i);
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

template <typename T>
std::size_t __qs(T m[], std::size_t left, std::size_t right)
{
    T tmpVal = m[left];
    while (left < right)
    {
        while (left < right && tmpVal <= m[right]) {
            --right;
        }
        m[left] = m[right];
        while (left < right && m[left] <= tmpVal) {
            ++left;
        }
        m[right] = m[left];
    }
    m[left] = tmpVal;
    return left;
}

template <typename T>
void __quicksort(T m[], int left, int right)
{
    if (left < right) {
        std::size_t index = __qs(m, left, right);
        __quicksort(m, left, index - 1);
        __quicksort(m, index + 1, right);
    }
}

template <typename T>
void quicksort(T m[], std::size_t n)
{
    __quicksort(m, 0, n - 1);
}

} // namespace pqalgo

#endif // PQALGO_SORT_H
