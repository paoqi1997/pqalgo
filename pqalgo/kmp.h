#ifndef PQALGO_KMP_H
#define PQALGO_KMP_H

#include <cstring>

namespace pqalgo
{

inline int bf(const char *s, const char *p)
{
    int lenS = std::strlen(s);
    int lenP = std::strlen(p);

    int i = 0, j = 0;

    while (i < lenS && j < lenP) {
        if (s[i] == p[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == lenP) {
        return i - j;
    } else {
        return -1;
    }
}

inline int* getNext(const char *p, std::size_t len)
{
    int *next = new int[len];
    next[0] = -1;

    int i = 0, j = -1;

    // bbc abcdab abcdabcdabde
    //     abcdabd
    //         abcdabd
    //            abcdabd
    //                abcdabd

    // 失配时，模式串向右移动的位数为：已匹配字符数 - 失配字符上一个字符所对应的最大长度值
    // 最大长度值为前缀与后缀的最大公共元素长度，比如 abcdab 的最大长度值为2，即 ab 的长度值

    // 移动的实际位数为 j - next[j]，next 数组各值代表当前字符之前的字符串中，有多大长度相同的前缀与后缀

    // 若 p 为 abcdabd，那么有以下 next 值：
    // a       next[0] = -1
    // ab      next[1] = 0
    // abc     next[2] = 0
    // abcd    next[3] = 0
    // abcda   next[4] = 0
    // abcdab  next[5] = 1
    // abcdabd next[6] = 2

    while (i < len - 1) {
        if (j == -1 || p[i] == p[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }

    return next;
}

inline int kmp(const char *s, const char *p)
{
    int lenS = std::strlen(s);
    int lenP = std::strlen(p);

    int *next = getNext(p, lenP);

    int i = 0, j = 0;

    while (i < lenS && j < lenP) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }

    delete []next;

    if (j == lenP) {
        return i - j;
    } else {
        return -1;
    }
}

} // namespace pqalgo

#endif // PQALGO_KMP_H
