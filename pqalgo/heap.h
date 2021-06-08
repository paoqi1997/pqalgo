#ifndef PQALGO_HEAP_H
#define PQALGO_HEAP_H

#include <cstddef>
#include <utility>

namespace pqalgo
{

template <typename RandomIt>
void __make_heap(RandomIt m, std::size_t rootIndex, std::size_t n)
{
    auto rootVal = m[rootIndex];
    std::size_t leafIndex = rootIndex * 2 + 1;

    while (leafIndex < n) {
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

template <typename RandomIt>
void make_heap(RandomIt first, RandomIt last)
{
    std::size_t n = last - first;

    for (int i = n / 2 - 1; i >= 0; --i) {
        __make_heap(first, i, n);
    }
}

template <typename RandomIt>
void push_heap(RandomIt first, RandomIt last)
{
    auto m = first;
    std::size_t n = last - first;

    int leafIndex = n - 1;
    int rootIndex = (leafIndex - 1) / 2;

    auto newVal = m[leafIndex];

    while (rootIndex >= 0) {
        if (m[rootIndex] >= newVal) {
            break;
        } else {
            m[leafIndex] = m[rootIndex];
            leafIndex = rootIndex;
            rootIndex = (leafIndex - 1) / 2;
        }
    }

    m[leafIndex] = newVal;
}

template <typename RandomIt>
void pop_heap(RandomIt first, RandomIt last)
{
    auto m = first;
    std::size_t n = last - first;

    std::swap(m[0], m[n - 1]);

    for (int i = (n - 1) / 2 - 1; i >= 0; --i) {
        __make_heap(m, i, n - 1);
    }
}

} // namespace pqalgo

#endif // PQALGO_HEAP_H
