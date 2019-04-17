#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <utility>

namespace pits
{

    /**
     * Range: m[0] - m[n - 1]
     */
    template <typename T>
    void bubblesort(T m[], uint32_t n)
    {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (m[j] > m[j + 1]) {
                    std::swap(m[j], m[j + 1]);
                }
            }
        }
    }

} // namespace pits

#endif // BUBBLESORT_H
