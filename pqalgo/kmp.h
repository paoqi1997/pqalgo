#ifndef PQALGO_KMP_H
#define PQALGO_KMP_H

#include <cstring>

namespace pqalgo
{

inline int* getNext(const char *p, std::size_t len)
{
    int *next = new int[len];
    next[0] = -1;

    int i = 0, j = -1;

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
