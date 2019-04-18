#ifndef MERGESORT_H
#define MERGESORT_H

namespace pits
{

template <typename T>
void merge(T m1[], T m2[], int low, int middle, int high)
{
    int i = low, j = middle + 1;
    while (i <= middle && j <= high) {
        if (m1[i] <= m1[j]) {
            m2[low++] = m1[i++];
        } else {
            m2[low++] = m1[j++];
        }
    }

    while (i <= middle) {
        m2[low++] = m1[i++];
    }
    while (j <= high) {
        m2[low++] = m1[j++];
    }
}

template <typename T>
void ms(T m1[], T m2[], int len, int n)
{
    int i = 0;
    while (i + 2 * len < n) {
        merge(m1, m2, i, i + len - 1, i + 2 * len - 1);
        i += 2 * len;
    }

    if (i + len < n) {
        merge(m1, m2, i, i + len - 1, n - 1);
    } else {
        for (int j = i; j < n; ++j) {
            m2[j] = m1[j];
        }
    }
}

template <typename T>
void mergesort(T m[], int n)
{
    T box[n];
    int i = 1;
    while (i < n) {
        ms(m, box, i, n); i *= 2;
        ms(box, m, i, n); i *= 2;
    }
}

} // namespace pits

#endif // MERGESORT_H
