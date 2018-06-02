#ifndef LIST_H
#define LIST_H

#include <memory>
#include <utility>

namespace pits
{
    template <typename T>
    struct nodes
    {
        T element; nodes<T> *prev, *next;

        nodes() : prev(nullptr), next(nullptr) {}

        nodes(const T& _element) : element(_element), prev(nullptr), next(nullptr) {}
    };

    template <typename T, typename Alloc> class list;

    template <typename T, typename Alloc>
    int list_compare(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        auto ps = lhs.data(0), pt = rhs.data(0);

        while (ps != nullptr && pt != nullptr)
        {
            if (ps->element != pt->element)
            {
                return ps->element - pt->element;
            }
            ps = ps->next, pt = pt->next;
        }
        return lhs.size() - rhs.size();
    }

    template <typename T, typename Alloc>
    bool operator == (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) == 0;
    }

    template <typename T, typename Alloc>
    bool operator != (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) != 0;
    }

    template <typename T, typename Alloc>
    bool operator <  (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) <  0;
    }

    template <typename T, typename Alloc>
    bool operator <= (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) <= 0;
    }

    template <typename T, typename Alloc>
    bool operator >  (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) >  0;
    }

    template <typename T, typename Alloc>
    bool operator >= (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return list_compare(lhs, rhs) >= 0;
    }

    template <typename T, typename Alloc>
    void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Alloc = std::allocator<T>>
    class list
    {
    public:
        using value_type      = T;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;

        using pointer         = nodes<T>*;
        using const_pointer   = const nodes<T>*;

        using reference       = T&;
        using const_reference = const T&;

        using allocator_type  = typename Alloc::template rebind<nodes<T>>::other;

        list();
        list(size_type, const T&);
        list(const list&);
        list(std::initializer_list<T>);

        ~list();

        list& operator = (const list&);
        list& operator = (std::initializer_list<T>);

        void assign();
        void assign(size_type, const T&);
        void assign(const list&);
        void assign(std::initializer_list<T>);

        pointer data(size_type) noexcept;
        const_pointer data(size_type) const noexcept;

        reference operator [] (size_type);
        const_reference operator [] (size_type) const;

        reference front() { return data(0)->element; }
        const_reference front() const { return data(0)->element; }

        reference back() { return data(cnt - 1)->element; }
        const_reference back() const { return data(cnt - 1)->element; }

        allocator_type get_allocator() const { return alloc; }

        void clear() noexcept;

        void insert(size_type, const T&);
        void insert(size_type, size_type, const T&);
        void insert(size_type, const list&);
        void insert(size_type, std::initializer_list<T>);

        template <typename... Args>
        void emplace(size_type pos, Args&&... args)
        { insert(pos, std::forward<Args>(args)...); }

        void erase(size_type);
        void erase(size_type, size_type);

        void push_front(const T& value) { insert(0, value); }
        void push_front(size_type count, const T& value) { insert(0, count, value); }
        void push_front(const list& rhs) { insert(0, rhs); }
        void push_front(std::initializer_list<T> init) { insert(0, init); }

        template <typename... Args>
        void emplace_front(Args&&... args)
        { insert(0, std::forward<Args>(args)...); }

        void pop_front() { erase(0); }

        void push_back(const T& value) { insert(cnt, value); }
        void push_back(size_type count, const T& value) { insert(cnt, count, value); }
        void push_back(const list& rhs) { insert(cnt, rhs); }
        void push_back(std::initializer_list<T> init) { insert(cnt, init); }

        template <typename... Args>
        void emplace_back(Args&&... args)
        { insert(cnt, std::forward<Args>(args)...); }

        void pop_back() { erase(cnt - 1); }

        void unique();

        template <typename BinaryPredicate>
        void unique(BinaryPredicate p);

        void remove(const T&);

        template <typename UnaryPredicate>
        void remove_if(UnaryPredicate p);

        void reverse() noexcept;

        size_type size() const noexcept { return cnt; }

        bool empty() const noexcept { return cnt == 0; }

        void swap(list& rhs) noexcept { std::swap(*this, rhs); }
    private:
        pointer ph, pt; size_type cnt; allocator_type alloc;
    };

    template <typename T, typename Alloc>
    list<T, Alloc>::list() : cnt(0)
    {
        ph = alloc.allocate(1); *ph = nodes<T>();

        pt = alloc.allocate(1); *pt = nodes<T>(); ph->next = pt; pt->prev = ph;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::list(size_type count, const T& value) : cnt(count)
    {
        ph = alloc.allocate(1); *ph = nodes<T>();

        pt = alloc.allocate(1); *pt = nodes<T>();

        auto p = ph;

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(value);

            p->next->prev = p; p = p->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::list(const list& rhs) : cnt(rhs.size())
    {
        ph = alloc.allocate(1); *ph = nodes<T>();

        pt = alloc.allocate(1); *pt = nodes<T>();

        auto p = ph, pu = rhs.data(0);

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(pu->element);

            p->next->prev = p; p = p->next; pu = pu->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::list(std::initializer_list<T> init) : cnt(init.size())
    {
        ph = alloc.allocate(1); *ph = nodes<T>();

        pt = alloc.allocate(1); *pt = nodes<T>();

        auto p = ph;

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(*it);

            p->next->prev = p; p = p->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>::~list()
    {
        /* 销毁头节点、尾节点及成员节点 */
        for (size_t i = 0; i < cnt + 2; ++i)
        {
            auto p = ph->next; alloc.deallocate(ph, 1); ph = p;
        }
    }

    template <typename T, typename Alloc>
    list<T, Alloc>& list<T, Alloc>::operator = (const list& rhs)
    {
        if (this != &rhs)
        {
            if (!empty()) clear();

            auto p = ph, pu = rhs.data(0); cnt = rhs.size();

            for (size_t i = 0; i < cnt; ++i)
            {
                p->next = alloc.allocate(1); *(p->next) = nodes<T>(pu->element);

                p->next->prev = p; p = p->next; pu = pu->next;
            }
            p->next = pt; pt->prev = p;
        } return *this;
    }

    template <typename T, typename Alloc>
    list<T, Alloc>& list<T, Alloc>::operator = (std::initializer_list<T> init)
    {
        if (!empty()) clear();

        auto p = ph; cnt = init.size();

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(*it);

            p->next->prev = p; p = p->next;
        }
        p->next = pt; pt->prev = p; return *this;
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::assign()
    {
        if (!empty()) clear();
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::assign(size_type count, const T& value)
    {
        if (!empty()) clear();

        auto p = ph; cnt = count;

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(value);

            p->next->prev = p; p = p->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::assign(const list& rhs)
    {
        if (!empty()) clear();

        auto p = ph, pu = rhs.data(0); cnt = rhs.size();

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(pu->element);

            p->next->prev = p; p = p->next; pu = pu->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::assign(std::initializer_list<T> init)
    {
        if (!empty()) clear();

        auto p = ph; cnt = init.size();

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = nodes<T>(*it);

            p->next->prev = p; p = p->next;
        }
        p->next = pt; pt->prev = p;
    }

    template <typename T, typename Alloc>
    typename list<T, Alloc>::pointer
    list<T, Alloc>::data(size_type pos) noexcept
    {
        if (pos < 0) {
            return ph;
        } else if (pos > cnt) {
            return nullptr;
        } else {
            auto p = ph->next;
            for (size_t i = 0; i < pos; ++i) {
                p = p->next;
            } return p;
        }
    }

    template <typename T, typename Alloc>
    typename list<T, Alloc>::const_pointer
    list<T, Alloc>::data(size_type pos) const noexcept
    {
        if (pos < 0) {
            return ph;
        } else if (pos > cnt) {
            return nullptr;
        } else {
            auto p = ph->next;
            for (size_t i = 0; i < pos; ++i) {
                p = p->next;
            } return p;
        }
    }

    template <typename T, typename Alloc>
    typename list<T, Alloc>::reference
    list<T, Alloc>::operator [] (size_type pos)
    {
        if (pos < 0) {
            return data(0)->element;
        } else if (pos >= cnt) {
            return data(cnt - 1)->element;
        } else {
            return data(pos)->element;
        }
    }

    template <typename T, typename Alloc>
    typename list<T, Alloc>::const_reference
    list<T, Alloc>::operator [] (size_type pos) const
    {
        if (pos < 0) {
            return data(0)->element;
        } else if (pos >= cnt) {
            return data(cnt - 1)->element;
        } else {
            return data(pos)->element;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::clear() noexcept
    {
        /* 保留头节点及尾节点 */
        auto pu = ph->next; ph->next = pt; pt->prev = ph;

        /* 销毁成员节点 */
        for ( ; cnt > 0; --cnt)
        {
            auto p = pu->next; alloc.deallocate(pu, 1); pu = p;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::insert(size_type pos, const T& value)
    {
        if (empty()) { assign(1, value); return; }

        auto p = alloc.allocate(1); *p = nodes<T>(value);

        auto pu = ph;

        if (pos < cnt)
        {
            for (size_t i = 0; i < pos; ++i) pu = pu->next;

            p->next = pu->next; pu->next->prev = p; pu->next = p; p->prev = pu; ++cnt;
        }
        else
        {
            for (size_t i = 0; i < cnt; ++i) pu = pu->next;

            pu->next = p; p->prev = pu; p->next = pt; pt->prev = p; ++cnt;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::insert(size_type pos, size_type count, const T& value)
    {
        if (empty()) { assign(count, value); return; }

        if (pos < cnt) {
            for (size_t i = 0; i < count; ++i) insert(pos, value);
        } else {
            for (size_t i = 0; i < count; ++i) insert(cnt, value);
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::insert(size_type pos, const list& rhs)
    {
        if (empty()) { assign(rhs); return; }

        auto p = rhs.data(0);

        if (pos < cnt) {
            for (size_t i = 0; i < rhs.size(); ++i) {
                insert(pos + i, p->element); p = p->next;
            }
        } else {
            for (size_t i = 0; i < rhs.size(); ++i) {
                insert(cnt + i, p->element); p = p->next;
            }
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::insert(size_type pos, std::initializer_list<T> init)
    {
        if (empty()) { assign(init); return; }

        if (pos < cnt) {
            for (auto it = init.begin(); it != init.end(); ++it) {
                insert(pos + it - init.begin(), *it);
            }
        } else {
            for (auto it = init.begin(); it != init.end(); ++it) {
                insert(cnt + it - init.begin(), *it);
            }
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::erase(size_type pos)
    {
        if (empty()) return;

        pointer p = ph, pu;

        if (pos < cnt - 1)
        {
            for (size_t i = 0; i < pos; ++i) p = p->next;

            pu = p->next; p->next = pu->next; pu->next->prev = p;

            alloc.deallocate(pu, 1); --cnt;
        }
        else if (pos == cnt - 1)
        {
            for (size_t i = 0; i < cnt - 1; ++i) p = p->next;

            alloc.deallocate(p->next, 1); p->next = pt; pt->prev = p; --cnt;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::erase(size_type lpos, size_type rpos)
    {
        if (lpos <= rpos)
        {
            if (lpos >= cnt) return;

            if (rpos >= cnt) rpos = cnt - 1;

            auto i = rpos - lpos + 1; while (i-- > 0) erase(lpos);
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::unique()
    {
        for (size_t i = 0; i + 1 < size(); )
        {
            if ((*this)[i] == (*this)[i + 1]) erase(i + 1); else ++i;
        }
    }

    template <typename T, typename Alloc>
    template <typename BinaryPredicate>
    void list<T, Alloc>::unique(BinaryPredicate p)
    {
        for (size_t i = 0; i + 1 < size(); )
        {
            if (p((*this)[i], (*this)[i + 1])) erase(i + 1); else ++i;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::remove(const T& value)
    {
        for (size_t i = 0; i < size(); )
        {
            if ((*this)[i] == value) erase(i); else ++i;
        }
    }

    template <typename T, typename Alloc>
    template <typename UnaryPredicate>
    void list<T, Alloc>::remove_if(UnaryPredicate p)
    {
        for (size_t i = 0; i < size(); )
        {
            if (p((*this)[i])) erase(i); else ++i;
        }
    }

    template <typename T, typename Alloc>
    void list<T, Alloc>::reverse() noexcept
    {
        pointer ps = nullptr, p = ph, pu = ph;

        for (size_t i = 0; i < cnt + 2; ++i)
        {
            p = p->next; ph->next = ps; ph->prev = p; ps = ph; ph = p;
        }
        ph = ps, pt = pu;
    }
}

#endif // LIST_H
