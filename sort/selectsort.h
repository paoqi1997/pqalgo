#ifndef SELECTSORT_H
#define SELECTSORT_H

#include <utility>

namespace pits
{

/**
 * range: [0, n - 1]
 */
template <typename T>
void selectsort(T m[], int n)
{
    for (int i = 0; i < n; ++i) {
        int index = i;
        for (int j = i + 1; j < n; ++j) {
            if (m[index] > m[j]) {
                index = j;
            }
        }
        std::swap(m[i], m[index]);
    }
}

} // namespace pits

#endif // SELECTSORT_H
