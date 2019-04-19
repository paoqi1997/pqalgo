#ifndef RADIXSORT_H
#define RADIXSORT_H

namespace pits
{

template <typename T> int maxdigit(T m[], int n);

template <>
int maxdigit(int m[], int n)
{
    int digit = 1, tmpVal = 10;
    for (int i = 0; i < n; ++i) {
        while (m[i] >= tmpVal) {
            ++digit;
            tmpVal *= 10;
        }
    }
    return digit;
}

/**
 * range: [0, n - 1]
 * tips: Only for nonnegative numbers.
 */
template <typename T> void radixsort(T m[], int n);

template <>
void radixsort(int m[], int n)
{
    int bucket[n];
    int counter[10];
    int radix = 1;
    int md = maxdigit(m, n);
    for (int d = 1; d <= md; ++d, radix *= 10) {
        for (int i = 0; i < 10; ++i) {
            counter[i] = 0;
        }

        for (int i = 0; i < n; ++i) {
            int j = (m[i] / radix) % 10;
            ++counter[j];
        }

        for (int i = 1; i < 10; ++i) {
            counter[i] += counter[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            int j = (m[i] / radix) % 10;
            bucket[counter[j] - 1] = m[i];
            --counter[j];
        }

        for (int i = 0; i < n; ++i) {
            m[i] = bucket[i];
        }
    }
}

} // namespace pits

#endif // RADIXSORT_H