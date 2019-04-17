#ifndef INSERTSORT_H
#define INSERTSORT_H

namespace pits
{

/**
 * range: [0, n - 1]
 */
template <typename T>
void insertsort(T m[], int n)
{
    for (int i = 1; i < n; ++i) {
        if (m[i - 1] > m[i]) {
            T tmpVal = m[i];
            int j = i;
            while (j > 0 && m[j - 1] > tmpVal) {
                m[j] = m[j - 1];
                --j;
            }
            m[j] = tmpVal;
        }
    }
}

} // namespace pits

#endif // INSERTSORT_H
