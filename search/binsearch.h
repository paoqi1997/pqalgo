#ifndef BINSEARCH_H
#define BINSEARCH_H

namespace pits
{

/**
 * range: [0, n - 1]
 * tips: The sequence must be sorted.
 */
template <typename T>
int binsearch(T m[], int n, T val)
{
    int low = 0, high = n;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (m[middle] == val) {
            return middle;
        } else if (m[middle] < val) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}

} // namespace pits

#endif // BINSEARCH_H
