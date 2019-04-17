#ifndef QUICKSORT_H
#define QUICKSORT_H

namespace pits
{

template <typename T>
int qs(T m[], int l, int r)
{
    T tmpVal = m[l];
    while (l < r) {
        while (l < r && m[r] >= tmpVal) {
            --r;
        }
        m[l] = m[r];
        while (l < r && m[l] <= tmpVal) {
            ++l;
        }
        m[r] = m[l];
    }
    m[l] = tmpVal;
    return l;
}

/**
 * range: [left, right]
 */
template <typename T>
void quicksort(T m[], int left, int right)
{
    if (left < right) {
        int index = qs(m, left, right);
        quicksort(m, left, index - 1);
        quicksort(m, index + 1, right);
    }
}

} // namespace pits

#endif // QUICKSORT_H
