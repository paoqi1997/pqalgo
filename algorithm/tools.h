#ifndef TOOLS_H
#define TOOLS_H

namespace pits
{
    using  int32_t = int;
    using uint32_t = unsigned int;

    template <typename T>
    void swap(T m[], uint32_t i, uint32_t j)
    {
        T temp; temp = m[i]; m[i] = m[j]; m[j] = temp;
    }

    template <typename T>
    void swap(T *p, T *q)
    {
        T *t = new T; *t = *p; *p = *q; *q = *t; delete t;
    }
}

#endif // TOOLS_H
