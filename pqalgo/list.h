#ifndef PQALGO_LIST_H
#define PQALGO_LIST_H

#include <cstddef>

namespace pqalgo
{

template <typename T>
struct ListNode
{
    ListNode() : prev(nullptr), next(nullptr) {}
    ListNode(T _element) : prev(nullptr), next(nullptr), element(_element) {}
    ListNode *prev;
    ListNode *next;
    T element;
};

template <typename T>
class list
{
public:
    list();
    ~list();
    void insert(std::size_t index, T element);
    ListNode<T>* begin() { return head->next; }
    const ListNode<T>* begin() const { return head->next; }
    ListNode<T>* end() { return tail; }
    const ListNode<T>* end() const { return tail; }
private:
    ListNode<T> *head;
    ListNode<T> *tail;
    std::size_t cnt;
};

template <typename T>
list<T>::list() : head(new ListNode<T>()), tail(new ListNode<T>()), cnt(0)
{
    head->next = tail;
    tail->prev = head;
}

template <typename T>
list<T>::~list()
{
    auto p = head->next;
    while (p != tail) {
        auto q = p->next;
        delete p;
        p = q;
    }
    cnt = 0;
    delete head;
    delete tail;
    head = tail = nullptr;
}

template <typename T>
void list<T>::insert(std::size_t index, T element)
{
    if (index > cnt) {
        return;
    }

    auto node = new ListNode<T>(element);

    if (index < cnt / 2) {
        auto p = head;
        std::size_t nextIdx = 0;
        while (p != nullptr && nextIdx++ != index) {
            p = p->next;
        }

        auto q = p->next;
        // prev部分
        q->prev = node;
        node->prev = p;
        // next部分
        p->next = node;
        node->next = q;
    } else {
        auto p = tail;
        if (cnt != 0) {
            std::size_t prevIdx = cnt;
            while (p != head && prevIdx-- != index) {
                p = p->prev;
            }
        }

        auto q = p->prev;
        // prev部分
        p->prev = node;
        node->prev = q;
        // next部分
        q->next = node;
        node->next = p;
    }

    ++cnt;
}

} // namespace pqalgo

#endif // PQALGO_LIST_H
