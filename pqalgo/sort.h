#ifndef PQALGO_SORT_H
#define PQALGO_SORT_H

#include <cstddef>
#include <utility>

namespace pqalgo
{

template <typename T>
void insertsort(T m[], std::size_t n)
{
    for (std::size_t i = 1; i < n; ++i)
    {
        T tmpVal = m[i];
        std::size_t j = i;
        // 自右向左遍历元素，比 m[i] 大的元素就往右挪，比 m[i] 小的元素就用 m[i] 替换之
        while (j > 0 && m[j - 1] > tmpVal)
        {
            m[j] = m[j - 1];
            --j;
        }
        m[j] = tmpVal;
    }
}

template <typename T>
void shellsort(T m[], std::size_t n)
{
    // 相比 insertsort 的区别就是 shellsort 是缩小增量排序
    for (std::size_t gap = n / 2; gap > 0; gap /= 2)
    {
        for (std::size_t i = gap; i < n; ++i)
        {
            T tmpVal = m[i];
            std::size_t j = i;
            while (j > 0 && m[j - gap] > tmpVal)
            {
                m[j] = m[j - gap];
                j -= gap;
            }
            m[j] = tmpVal;
        }
    }
}

template <typename T>
void selectsort(T m[], std::size_t n)
{
    for (std::size_t i = 0; i < n - 1; ++i)
    {
        std::size_t minIdx = i;
        // 自左向右遍历元素，与 m[i] 为起始值，记录最小元素对应的索引，遍历结束后将其与 m[i] 交换
        for (std::size_t j = i + 1; j < n; ++j)
        {
            if (m[minIdx] > m[j]) {
                minIdx = j;
            }
        }
        std::swap(m[i], m[minIdx]);
    }
}

template <typename T>
void __heapsort(T m[], std::size_t rootIndex, std::size_t n)
{
    // 面对子树
    T rootVal = m[rootIndex];
    // 根节点的左叶子节点
    std::size_t leafIndex = rootIndex * 2 + 1;
    while (leafIndex < n)
    {
        // 右叶子节点存在并且它比左叶子节点要大
        if (leafIndex + 1 < n && m[leafIndex] < m[leafIndex + 1]) {
            // 取得右叶子节点的索引
            ++leafIndex;
        }
        // 根节点比叶子节点小
        if (rootVal < m[leafIndex]) {
            // 把叶子节点换到根节点
            m[rootIndex] = m[leafIndex];
            rootIndex = leafIndex, leafIndex = rootIndex * 2 + 1;
        } else {
            break;
        }
    }
    m[rootIndex] = rootVal;
}

template <typename T>
void heapsort(T m[], std::size_t n)
{
    // 大根堆有这样的定义：m[i] >= m[2 * i + 1] && m[i] >= m[2 * i + 2]
    // 小根堆有这样的定义：m[i] <= m[2 * i + 1] && m[i] <= m[2 * i + 2]

    // 构建初始堆，这里是大根堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        __heapsort(m, i, n);
    }
    for (std::size_t i = 1; i < n; ++i)
    {
        // 交换堆顶元素和末尾元素，使最大元素沉至数组末端
        std::swap(m[0], m[n - i]);
        __heapsort(m, 0, n - i);
    }
}

template <typename T>
void bubblesort(T m[], std::size_t n)
{
    for (std::size_t i = 0; i < n - 1; ++i)
    {
        for (std::size_t j = 0; j < n - i - 1; ++j)
        {
            if (m[j] > m[j + 1]) {
                std::swap(m[j], m[j + 1]);
            }
        }
    }
}

template <typename T>
std::size_t __qs(T m[], std::size_t left, std::size_t right)
{
    T tmpVal = m[left];
    while (left < right)
    {
        while (left < right && tmpVal <= m[right]) {
            --right;
        }
        m[left] = m[right];
        while (left < right && m[left] <= tmpVal) {
            ++left;
        }
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
        __quicksort(m, left, index - 1);
        __quicksort(m, index + 1, right);
    }
}

template <typename T>
void quicksort(T m[], std::size_t n)
{
    __quicksort(m, 0, n - 1);
}

template <typename T>
void __ms(T m1[], T m2[], std::size_t low, std::size_t middle, std::size_t high)
{
    std::size_t i = low, j = middle + 1;
    while (i <= middle && j <= high)
    {
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
void __mergesort(T m1[], T m2[], std::size_t len, std::size_t n)
{
    std::size_t i = 0;
    while (i + len * 2 <= n)
    {
        __ms(m1, m2, i, i + len - 1, i + len * 2 - 1);
        i += len * 2;
    }

    if (i + len < n) {
        __ms(m1, m2, i, i + len - 1, n - 1);
    } else {
        for (std::size_t j = i; j < n; ++j) {
            m2[j] = m1[j];
        }
    }
}

template <typename T>
void mergesort(T m[], std::size_t n)
{
    auto m2 = new T[n];
    for (std::size_t i = 1; i < n; )
    {
        __mergesort(m, m2, i, n);
        i *= 2;
        __mergesort(m2, m, i, n);
        i *= 2;
    }
    delete []m2;
}

template <typename T>
std::size_t __radixsort(T m[], std::size_t n);

template <>
std::size_t __radixsort(int m[], std::size_t n)
{
    std::size_t digit = 1, maxVal = 10;
    for (std::size_t i = 0; i < n; ++i)
    {
        while (m[i] >= maxVal) {
            ++digit;
            maxVal *= 10;
        }
    }
    return digit;
}

template <typename T>
void radixsort(T m[], std::size_t n);

template <>
void radixsort(int m[], std::size_t n)
{
    auto buckets = new int[n];
    int counters[10];
    int radix = 1;
    std::size_t maxDigit = __radixsort(m, n);
    for (std::size_t d = 1; d <= maxDigit; ++d, radix *= 10)
    {
        for (std::size_t i = 0; i < 10; ++i) {
            counters[i] = 0;
        }

        for (std::size_t i = 0; i < n; ++i) {
            std::size_t idx = (m[i] / radix) % 10;
            ++counters[idx];
        }

        for (std::size_t i = 1; i < 10; ++i) {
            counters[i] += counters[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            std::size_t j = (m[i] / radix) % 10;
            buckets[counters[j] - 1] = m[i];
            --counters[j];
        }

        for (std::size_t i = 0; i < n; ++i) {
            m[i] = buckets[i];
        }
    }
    delete []buckets;
}

} // namespace pqalgo

#endif // PQALGO_SORT_H
