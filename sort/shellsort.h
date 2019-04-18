#ifndef SHELLSORT_H
#define SHELLSORT_H

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
            int j = i;
            while (j >= gap && m[j - gap] > tmpVal) {
                m[j] = m[j - gap];
                j -= gap;
            }
            m[j] = tmpVal;
        }
    }
}

} // namespace pits

#endif // SHELLSORT_H
