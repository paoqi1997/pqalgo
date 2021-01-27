#ifndef PQALGO_LIST_H
#define PQALGO_LIST_H

#include <cstddef>
#include <utility>

namespace pqalgo
{

template <typename T>
struct ListNode
{
    ListNode() : prev(nullptr), next(nullptr) {}
    ListNode(const T& _element) : prev(nullptr), next(nullptr), element(_element) {}
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
    bool insert(std::size_t index, const T& element);
    bool erase(std::size_t index);
    void reverse();
    ListNode<T>* begin() { return head->next; }
    const ListNode<T>* begin() const { return head->next; }
    ListNode<T>* end() { return tail; }
    const ListNode<T>* end() const { return tail; }
    ListNode<T>* rbegin() { return tail->prev; }
    const ListNode<T>* rbegin() const { return tail->prev; }
    ListNode<T>* rend() { return head; }
    const ListNode<T>* rend() const { return head; }
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
bool list<T>::insert(std::size_t index, const T& element)
{
    if (index > cnt) {
        return false;
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
            while (p != nullptr && prevIdx-- != index) {
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
    return true;
}

template <typename T>
bool list<T>::erase(std::size_t index)
{
    if (index > cnt || cnt == 0) {
        return false;
    }

    if (index < cnt / 2) {
        auto p = head;
        std::size_t nextIdx = 0;
        while (p != nullptr && nextIdx++ != index) {
            p = p->next;
        }

        auto node = p->next;
        if (node == nullptr) {
            return false;
        }

        auto q = node->next;
        delete node;
        p->next = q;
        q->prev = p;
    } else {
        auto p = tail;
        std::size_t prevIdx = cnt;
        while (p != nullptr && --prevIdx != index) {
            p = p->prev;
        }

        auto node = p->prev;
        if (node == nullptr) {
            return false;
        }

        auto q = node->prev;
        delete node;
        q->next = p;
        p->prev = q;
    }

    --cnt;
    return true;
}

template <typename T>
void list<T>::reverse()
{
    auto p = head->next;
    if (p == tail || p->next == tail) {
        return;
    }

    ListNode<T> *node = head;
    while (p != tail) {
        auto q = p->next;
        p->next = node;
        node->prev = p;
        node = p;
        p = q;
    }

    tail->next = node;
    node->prev = tail;

    std::swap(head, tail);

    head->prev = nullptr;
    tail->next = nullptr;
}

} // namespace pqalgo

#endif // PQALGO_LIST_H
