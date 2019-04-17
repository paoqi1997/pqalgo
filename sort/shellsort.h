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
            T tmpVal = m[i];
            int j = i - gap;
            while (j >= 0 && m[j] > tmpVal) {
                m[j + gap] = m[j];
                j -= gap;
            }
            m[j + gap] = tmpVal;
        }
    }
}

} // namespace pits

#endif // SHELLSORT_H
