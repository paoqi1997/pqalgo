#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <utility>

namespace pits
{
    template <typename Key>
    struct hash
    {
        size_t operator()(const Key& key) const;
    };

    template <>
    struct hash<std::string>
    {
        size_t operator()(const std::string& key) const
        {
            unsigned long hash = 0;

            for (auto c : key)
            {
                hash = hash * 33 + c;
            }

            return hash;
        }
    };

    template <typename Key, typename T>
    struct hnode
    {
        std::pair<Key, T> kv; hnode<Key, T> *next;

        hnode() : next(nullptr) {}

        hnode(const std::pair<Key, T>& p) : kv(std::make_pair(p.first, p.second)), next(nullptr) {}

        hnode(const Key& key, const T& element) : kv(std::make_pair(key, element)), next(nullptr) {}
    };

    template <typename Key, typename T, typename Hash, typename Alloc> class hashtable;

    template <typename Key, typename T, typename Hash, typename Alloc>
    bool operator == (const hashtable<Key, T, Hash, Alloc>& lhs, const hashtable<Key, T, Hash, Alloc>& rhs)
    {
        size_t lbct = lhs.bucket_count(), rbct = rhs.bucket_count();

        // 桶的数量不同
        if (lbct != rbct) return false;

        size_t tbct = (lbct < rbct) ? lbct : rbct;

        for (size_t i = 0; i < tbct; ++i)
        {
            size_t let = lhs.bucket_size(i), ret = rhs.bucket_size(i);

            // 桶内的元素数量不同
            if (let != ret) return false;

            auto pl = lhs.data(i)->next, pr = rhs.data(i)->next;

            while (pl != nullptr && pr != nullptr)
            {
                if (pl->kv.first != pr->kv.first) {
                    return false;
                } else {
                    if (pl->kv.second != pr->kv.second) {
                        return false;
                    } else {
                        pl = pl->next, pr = pr->next;
                    }
                }
            }
        } return (lhs.size() == rhs.size()) ? true : false;
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    bool operator != (const hashtable<Key, T, Hash, Alloc>& lhs, const hashtable<Key, T, Hash, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void swap(hashtable<Key, T, Hash, Alloc>& lhs, hashtable<Key, T, Hash, Alloc>& rhs) noexcept { lhs.swap(rhs); }

    template <typename Key, typename T,
              typename Hash = hash<Key>,
              typename Alloc = std::allocator<std::pair<Key, T>>>
    class hashtable
    {
    public:
        using key_type               = Key;
        using mapped_type            = T;

        using value_type             = std::pair<Key, T>;
        using size_type              = size_t;
        using difference_type        = ptrdiff_t;

        using pointer                = hnode<Key, T>*;
        using const_pointer          = const hnode<Key, T>*;

        using reference              = value_type&;
        using const_reference        = const value_type&;

        using hasher                 = Hash;
        using bucket_allocator_type  = typename Alloc::template rebind<pointer>::other;
        using element_allocator_type = typename Alloc::template rebind<hnode<Key, T>>::other;

        enum { BUCKET_COUNT = 10 };

        hashtable();
        hashtable(size_type);
        hashtable(const Hash&);
        hashtable(size_type, const Hash&);

        hashtable(const hashtable&);
        hashtable(std::initializer_list<value_type>);

        hashtable& operator = (const hashtable&);
        hashtable& operator = (std::initializer_list<value_type>);

        ~hashtable() noexcept;

        pointer data(size_type) noexcept;
        const_pointer data(size_type) const noexcept;

        T& operator [] (const Key&);

        float load_factor() const { return static_cast<float>(ect) / bct; }

        size_type bucket(const Key& key) const { return hashfunc(key) % bct; }

        bucket_allocator_type get_bucket_allocator() const { return blloc; }
        element_allocator_type get_element_allocator() const { return elloc; }

        void clear() noexcept;

        void output() const noexcept;

        void insert(const value_type&);
        void insert(const Key&, const T&);

        void erase(const Key&);

        bool contains(const Key&) const;

        size_type count(const Key&) const;

        size_type bucket_size(size_type) const;

        size_type bucket_count() const { return bct; }

        size_type size() const noexcept { return ect; }

        bool empty() const noexcept { return ect == 0; }

        hasher hash_function() const { return hashfunc; }

        void swap(hashtable& rhs) noexcept { std::swap(*this, rhs); }
    private:
        size_type bct;
        bucket_allocator_type blloc;
        size_type ect;
        element_allocator_type elloc;
        hnode<Key, T> **buckets; hasher hashfunc;
    };

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable()
    {
        bct = BUCKET_COUNT, ect = 0;

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable(size_type count)
    {
        bct = count, ect = 0;

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable(const Hash& hash) : hashfunc(hash)
    {
        bct = BUCKET_COUNT, ect = 0;

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable(size_type count, const Hash& hash) : hashfunc(hash)
    {
        bct = count, ect = 0;

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable(const hashtable& rhs) : hashfunc(rhs.hash_function())
    {
        bct = rhs.bucket_count(), ect = rhs.size();

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();

            auto p = buckets[i], pt = rhs.data(i)->next;

            while (pt != nullptr)
            {
                p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(pt->kv.first, pt->kv.second);

                p = p->next, pt = pt->next;
            }
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::hashtable(std::initializer_list<value_type> init)
    {
        bct = BUCKET_COUNT, ect = 0;

        buckets = blloc.allocate(bct);

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            auto p = buckets[bucket(it->first)];

            if (contains(it->first))
            {
                while (p != nullptr)
                {
                    if (p->kv.first == it->first) {
                        break;
                    } else {
                        p = p->next;
                    }
                } p->kv.second = it->second;
            }
            else
            {
                while (p->next != nullptr) p = p->next;

                ++ect;

                p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(it->first, it->second);
            }
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>&
    hashtable<Key, T, Hash, Alloc>::operator = (const hashtable& rhs)
    {
        if (this != &rhs)
        {
            if (!empty()) clear();

            if (bct != rhs.bucket_count())
            {
                blloc.deallocate(buckets, bct);
                bct = rhs.bucket_count(); buckets = blloc.allocate(bct);
            }

            ect = rhs.size();

            hashfunc = rhs.hash_function();

            for (size_t i = 0; i < bct; ++i)
            {
                buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();

                auto p = buckets[i], pt = rhs.data(i)->next;

                while (pt != nullptr)
                {
                    p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(pt->kv.first, pt->kv.second);

                    p = p->next, pt = pt->next;
                }
            }
        } return *this;
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>&
    hashtable<Key, T, Hash, Alloc>::operator = (std::initializer_list<value_type> init)
    {
        if (!empty()) clear();

        if (bct != BUCKET_COUNT)
        {
            blloc.deallocate(buckets, bct);
            bct = BUCKET_COUNT; buckets = blloc.allocate(bct);
        }

        ect = 0;

        for (size_t i = 0; i < bct; ++i)
        {
            buckets[i] = elloc.allocate(1); *buckets[i] = hnode<Key, T>();
        }

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            auto p = buckets[bucket(it->first)];

            if (contains(it->first))
            {
                while (p != nullptr)
                {
                    if (p->kv.first == it->first) {
                        break;
                    } else {
                        p = p->next;
                    }
                } p->kv.second = it->second;
            }
            else
            {
                while (p->next != nullptr) p = p->next;

                ++ect;

                p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(it->first, it->second);
            }
        } return *this;
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    hashtable<Key, T, Hash, Alloc>::~hashtable() noexcept
    {
        for (size_t i = 0; i < bct; ++i)
        {
            auto ph = buckets[i];

            while (ph != nullptr)
            {
                auto p = ph->next; elloc.deallocate(ph, 1); ph = p;
            }
        } blloc.deallocate(buckets, bct);
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    typename hashtable<Key, T, Hash, Alloc>::pointer
    hashtable<Key, T, Hash, Alloc>::data(size_type pos) noexcept
    {
        if (pos < 0) {
            return buckets[0];
        } else {
            return (pos >= bct) ? buckets[bct - 1] : buckets[pos];
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    typename hashtable<Key, T, Hash, Alloc>::const_pointer
    hashtable<Key, T, Hash, Alloc>::data(size_type pos) const noexcept
    {
        if (pos < 0) {
            return buckets[0];
        } else {
            return (pos >= bct) ? buckets[bct - 1] : buckets[pos];
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    T& hashtable<Key, T, Hash, Alloc>::operator [] (const Key& key)
    {
        auto p = buckets[bucket(key)];

        if (contains(key))
        {
            while (p != nullptr)
            {
                if (p->kv.first == key) {
                    break;
                } else {
                    p = p->next;
                }
            } return p->kv.second;
        }
        else
        {
            while (p->next != nullptr) p = p->next;

            ++ect;

            p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>();

            p->next->kv.first = key; return p->next->kv.second;
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void hashtable<Key, T, Hash, Alloc>::clear() noexcept
    {
        for (size_t i = 0; i < bct; ++i)
        {
            auto pt = buckets[i]->next;

            while (pt != nullptr)
            {
                --ect;

                auto p = pt->next; elloc.deallocate(pt, 1); pt = p;
            }

            buckets[i]->next = nullptr;
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void hashtable<Key, T, Hash, Alloc>::output() const noexcept
    {
        for (size_t i = 0; i < bct; ++i)
        {
            auto p = buckets[i]->next;

            std::cout << '[' << "Bucket" << ' ' << i + 1 << ']' << std::endl;

            while (p != nullptr)
            {
                std::cout << p->kv.first << ':' << p->kv.second << std::endl;

                p = p->next;
            }
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void hashtable<Key, T, Hash, Alloc>::insert(const value_type& value)
    {
        auto p = buckets[bucket(value.first)];

        if (contains(value.first))
        {
            while (p != nullptr)
            {
                if (p->kv.first == value.first) {
                    break;
                } else {
                    p = p->next;
                }
            } p->kv.second = value.second;
        }
        else
        {
            while (p->next != nullptr) p = p->next;

            ++ect;

            p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(value.first, value.second);
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void hashtable<Key, T, Hash, Alloc>::insert(const Key& key, const T& element)
    {
        auto p = buckets[bucket(key)];

        if (contains(key))
        {
            while (p != nullptr)
            {
                if (p->kv.first == key) {
                    break;
                } else {
                    p = p->next;
                }
            } p->kv.second = element;
        }
        else
        {
            while (p->next != nullptr) p = p->next;

            ++ect;

            p->next = elloc.allocate(1); *(p->next) = hnode<Key, T>(key, element);
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    void hashtable<Key, T, Hash, Alloc>::erase(const Key& key)
    {
        if (!contains(key)) return;

        auto p = buckets[bucket(key)];

        while (p->next != nullptr)
        {
            if (p->next->kv.first == key) {
                auto pt = p->next; p->next = pt->next;
                elloc.deallocate(pt, 1);
                --ect; break;
            } else {
                p = p->next;
            }
        }
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    bool hashtable<Key, T, Hash, Alloc>::contains(const Key& key) const
    {
        size_t pos = bucket(key);

        for (auto p = buckets[pos]; p != nullptr; p = p->next)
        {
            if (p->kv.first == key)
            {
                return true;
            }
        } return false;
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    typename hashtable<Key, T, Hash, Alloc>::size_type
    hashtable<Key, T, Hash, Alloc>::count(const Key& key) const
    {
        size_t pos = bucket(key);

        for (auto p = buckets[pos]; p != nullptr; p = p->next)
        {
            if (p->kv.first == key)
            {
                return 1;
            }
        } return 0;
    }

    template <typename Key, typename T, typename Hash, typename Alloc>
    typename hashtable<Key, T, Hash, Alloc>::size_type
    hashtable<Key, T, Hash, Alloc>::bucket_size(size_type n) const
    {
        size_t cnt = 0; auto p = data(n)->next;

        while (p != nullptr)
        {
            ++cnt; p = p->next;
        }

        return cnt;
    }
}

#endif // HASHTABLE_H
