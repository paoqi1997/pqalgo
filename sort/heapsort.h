#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <utility>

namespace pits
{

template <typename T>
void hs(T m[], int rootIndex, int n)
{
    T rootVal = m[rootIndex];
    int leafIndex = 2 * rootIndex + 1;
    while (leafIndex < n) {
        if (leafIndex + 1 < n && m[leafIndex] < m[leafIndex + 1]) {
            ++leafIndex;
        }
        if (rootVal < m[leafIndex]) {
            m[rootIndex] = m[leafIndex];
            rootIndex = leafIndex, leafIndex = 2 * rootIndex + 1;
        } else {
            break;
        }
    }
    m[rootIndex] = rootVal;
}

/**
 * range: [0, n - 1]
 */
template <typename T>
void heapsort(T m[], int n)
{
    for (int i = n / 2 - 1; i >= 0; --i) {
        hs(m, i, n);
    }
    for (int i = 1; i < n; ++i) {
        std::swap(m[0], m[n - i]);
        hs(m, 0, n - i);
    }
}

} // namespace pits

#endif // HEAPSORT_H
