#ifndef PQALGO_HEAP_H
#define PQALGO_HEAP_H

#include <cstddef>

namespace pqalgo
{

template <typename RandomIt>
void make_heap(RandomIt first, RandomIt last)
{
    std::size_t n = last - first;

    for (int i = n / 2; i >= 0; --i) {
        auto m = first;
        std::size_t rootIndex = i;

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
}

} // namespace pqalgo

#endif // PQALGO_HEAP_H
