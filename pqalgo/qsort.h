#ifndef PQALGO_QSORT_H
#define PQALGO_QSORT_H

#include <cstddef>

namespace pqalgo
{

template <typename T>
std::size_t __qs(T m[], std::size_t left, std::size_t right)
{
    // 第一个值作为基准值，即在 m[left] 处挖了个坑
    T tmpVal = m[left];
    while (left < right)
    {
        // 自右向左寻找比基准值小的元素
        while (left < right && tmpVal <= m[right]) {
            --right;
        }
        // 将 m[right] 处找到的元素填到 m[left] 处，同时形成新的 m[right] 坑
        // 把比基准值小的元素放到左边
        m[left] = m[right];
        // 自左向右寻找比基准值大的元素
        while (left < right && m[left] <= tmpVal) {
            ++left;
        }
        // 将 m[left] 处找到的元素填到 m[right] 处，同时形成新的 m[left] 坑
        // 把比基准值大的元素放到右边
        m[right] = m[left];
    }
    m[left] = tmpVal;
    return left;
}

template <typename T>
void __quicksort(T m[], int left, int right)
{
    if (left < right) {
        std::size_t index = __qs(m, left, right);
        // 对左右区间重复以上步骤
        __quicksort(m, left, index - 1);
        __quicksort(m, index + 1, right);
    }
}

template <typename T>
void quicksort(T m[], std::size_t n)
{
    __quicksort(m, 0, n - 1);
}

} // namespace pqalgo

#endif // PQALGO_QSORT_H
