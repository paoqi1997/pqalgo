#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <utility>

namespace pits
{

/**
 * range: [0, n - 1]
 */
template <typename T>
void shellsort(T m[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            for (int j = i - gap; j >= 0 && m[j] > m[j + gap]; j -= gap) {
                std::swap(m[j], m[j + gap]);
            }
        }
    }
}

} // namespace pits

#endif // SHELLSORT_H
