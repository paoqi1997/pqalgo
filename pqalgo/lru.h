#ifndef PQALGO_LRU_H
#define PQALGO_LRU_H

#include <list>
#include <unordered_map>
#include <utility>

namespace pqalgo
{

template <typename K, typename V>
class LRU
{
public:
    using value_type      = std::pair<K, V>;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = typename std::list<std::pair<K, V>>::iterator;
    using const_iterator  = const iterator;

    LRU(std::size_t capacity) : m_capacity(capacity) {}
    V& operator [] (const K& key);
public:
    reference front() { return m_lru.front(); }
    const_reference front() const { return m_lru.front(); }
    reference back() { return m_lru.back(); }
    const_reference back() const { return m_lru.back(); }

    iterator begin() { return m_lru.begin(); }
    const_iterator begin() const { return m_lru.begin(); }
    iterator end() { return m_lru.end(); }
    const_iterator end() const { return m_lru.end(); }
private:
    std::size_t m_capacity;
    std::list<std::pair<K, V>> m_lru;
    std::unordered_map<K, iterator> m_tbl;
};

template <typename K, typename V>
V& LRU<K, V>::operator [] (const K& key)
{
    auto it = m_tbl.find(key);
    if (it != m_tbl.end()) {
        m_lru.splice(m_lru.begin(), m_lru, it->second);
        it->second->second = V();
        return it->second->second;
    }

    m_lru.emplace_front(key, V());
    m_tbl[key] = m_lru.begin();

    if (m_tbl.size() > m_capacity) {
        m_tbl.erase(m_lru.back().first);
        m_lru.pop_back();
    }

    return m_lru.begin()->second;
}

} // namespace pqalgo

#endif // PQALGO_LRU_H
