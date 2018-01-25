#ifndef LABEL_H
#define LABEL_H

namespace pits
{
    template <typename T>
    struct node
    {
        T element;
        node<T> *next;

        node() : element(static_cast<T>(0)), next(nullptr) {}

        node(const T& value) : element(value), next(nullptr) {}
    };

    template <typename T>
    struct nodes
    {
        T element;
        nodes<T> *prev, *next;

        nodes() : element(static_cast<T>(0)), prev(nullptr), next(nullptr) {}

        nodes(const T& value) : element(value), prev(nullptr), next(nullptr) {}
    };
}

#endif // LABEL_H
