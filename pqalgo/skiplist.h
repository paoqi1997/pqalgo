#ifndef PQALGO_SKIPLIST_H
#define PQALGO_SKIPLIST_H

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace pqalgo
{

inline void initRandom()
{
    std::srand(std::time(nullptr));
}

inline int Random(int n)
{
    return std::rand() % n;
}

inline int RandomLevel(int maxlevel)
{
    int level = 1;

    for (int i = 1; Random(2) == 1 && i < maxlevel; ++i) {
        ++level;
    }

    return level;
}

template <typename K, typename V>
struct SkipListNode
{
    SkipListNode(const K& _key, const V& _value, std::size_t _level)
        : level(_level), key(_key), value(_value)
    {
        next = new SkipListNode*[_level];
        for (std::size_t i = 0; i < _level; ++i) {
            next[i] = nullptr;
        }
    }
    ~SkipListNode() { delete []next; }
    SkipListNode **next;
    std::size_t level;
    K key;
    V value;
};

template <typename K, typename V>
class skiplist
{
public:
    skiplist() : head(new SkipListNode<K, V>(K(), V(), MaxLevel)) {}
    ~skiplist();
    V& operator [] (const K& key);
    bool remove(const K& key);
    SkipListNode<K, V>* find(const K& key) const;
    void print() const;
private:
    static const std::size_t MaxLevel = 4;
private:
    SkipListNode<K, V> *head;
};

template <typename K, typename V>
skiplist<K, V>::~skiplist()
{
    auto p = head;
    while (p != nullptr) {
        auto q = p->next[0];
        delete p;
        p = q;
    }
    head = nullptr;
}

template <typename K, typename V>
V& skiplist<K, V>::operator [] (const K& key)
{
    auto pnode = find(key);
    if (pnode != nullptr && pnode->key == key) {
        return pnode->value;
    }

    int level = RandomLevel(MaxLevel);

    auto p = head;
    auto node = new SkipListNode<K, V>(key, V(), level);

    for (int i = level - 1; i >= 0; --i) {
        while (p->next[i] != nullptr && p->next[i]->key < key) {
            p = p->next[i];
        }

        node->next[i] = p->next[i];
        p->next[i] = node;
    }

    return node->value;
}

template <typename K, typename V>
bool skiplist<K, V>::remove(const K& key)
{
    auto pnode = find(key);
    if (pnode == nullptr) {
        return false;
    }

    auto p = head;

    for (int i = pnode->level - 1; i >= 0; --i) {
        while (p->next[i] != nullptr && p->next[i]->key < key) {
            p = p->next[i];
        }

        p->next[i] = p->next[i]->next[i];
    }

    delete pnode;
    return true;
}

template <typename K, typename V>
SkipListNode<K, V>* skiplist<K, V>::find(const K& key) const
{
    auto p = head;

    for (int i = MaxLevel - 1; i >= 0; --i) {
        while (p->next[i] != nullptr && p->next[i]->key < key) {
            p = p->next[i];
        }
    }

    if (p->next[0] != nullptr && p->next[0]->key == key) {
        return p->next[0];
    } else {
        return nullptr;
    }
}

template <typename K, typename V>
void skiplist<K, V>::print() const
{
    for (int i = MaxLevel - 1; i >= 0; --i) {
        auto p = head;

        std::cout << "level(" << i << "): ";

        while (p->next[i] != nullptr) {
            std::cout << p->next[i]->key << ':' << p->next[i]->value << ' ';
            p = p->next[i];
        }

        std::cout << std::endl;
    }
}

} // namespace pqalgo

#endif // PQALGO_SKIPLIST_H
