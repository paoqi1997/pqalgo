#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <memory>
#include <utility>

namespace pits
{
    template <typename T>
    struct node
    {
        T element; node<T> *next;

        node() : next(nullptr) {}

        node(const T& _element) : element(_element), next(nullptr) {}
    };

    template <typename T, typename Alloc> class forward_list;

    template <typename T, typename Alloc>
    int forward_list_compare
    (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
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
    bool operator == (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) == 0;
    }

    template <typename T, typename Alloc>
    bool operator != (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) != 0;
    }

    template <typename T, typename Alloc>
    bool operator <  (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) <  0;
    }

    template <typename T, typename Alloc>
    bool operator <= (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) <= 0;
    }

    template <typename T, typename Alloc>
    bool operator >  (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) >  0;
    }

    template <typename T, typename Alloc>
    bool operator >= (const forward_list<T, Alloc>& lhs, const forward_list<T, Alloc>& rhs)
    {
        return forward_list_compare(lhs, rhs) >= 0;
    }

    template <typename T, typename Alloc>
    void swap(forward_list<T, Alloc>& lhs, forward_list<T, Alloc>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Alloc = std::allocator<T>>
    class forward_list
    {
    public:
        using value_type      = T;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;

        using pointer         = node<T>*;
        using const_pointer   = const node<T>*;

        using reference       = T&;
        using const_reference = const T&;

        using allocator_type  = typename Alloc::template rebind<node<T>>::other;

        forward_list();
        forward_list(size_type, const T&);
        forward_list(const forward_list&);
        forward_list(std::initializer_list<T>);

        ~forward_list();

        forward_list& operator = (const forward_list&);
        forward_list& operator = (std::initializer_list<T>);

        void assign();
        void assign(size_type, const T&);
        void assign(const forward_list&);
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
        void insert(size_type, const forward_list&);
        void insert(size_type, std::initializer_list<T>);

        template <typename... Args>
        void emplace(size_type pos, Args&&... args)
        { insert(pos, std::forward<Args>(args)...); }

        void erase(size_type);
        void erase(size_type, size_type);

        void push_front(const T& value) { insert(0, value); }
        void push_front(size_type count, const T& value) { insert(0, count, value); }
        void push_front(const forward_list& rhs) { insert(0, rhs); }
        void push_front(std::initializer_list<T> init) { insert(0, init); }

        template <typename... Args>
        void emplace_front(Args&&... args)
        { insert(0, std::forward<Args>(args)...); }

        void pop_front() { erase(0); }

        void push_back(const T& value) { insert(cnt, value); }
        void push_back(size_type count, const T& value) { insert(cnt, count, value); }
        void push_back(const forward_list& rhs) { insert(cnt, rhs); }
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

        void swap(forward_list& rhs) noexcept { std::swap(*this, rhs); }
    private:
        pointer ph; size_type cnt; allocator_type alloc;
    };

    template <typename T, typename Alloc>
    forward_list<T, Alloc>::forward_list() : cnt(0)
    {
        ph = alloc.allocate(1); *ph = node<T>();
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>::forward_list(size_type count, const T& value) : cnt(count)
    {
        ph = alloc.allocate(1); *ph = node<T>();

        auto p = ph;

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(value);

            p = p->next;
        }
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>::forward_list(const forward_list& rhs) : cnt(rhs.size())
    {
        ph = alloc.allocate(1); *ph = node<T>();

        auto p = ph, pt = rhs.data(0);

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(pt->element);

            p = p->next; pt = pt->next;
        }
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>::forward_list(std::initializer_list<T> init) : cnt(init.size())
    {
        ph = alloc.allocate(1); *ph = node<T>();

        auto p = ph;

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(*it);

            p = p->next;
        }
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>::~forward_list()
    {
        /* 销毁头节点及成员节点 */
        for (size_t i = 0; i < cnt + 1; ++i)
        {
            auto p = ph->next; alloc.deallocate(ph, 1); ph = p;
        }
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>& forward_list<T, Alloc>::operator = (const forward_list& rhs)
    {
        if (this != &rhs)
        {
            if (!empty()) clear();

            auto p = ph, pt = rhs.data(0); cnt = rhs.size();

            for (size_t i = 0; i < cnt; ++i)
            {
                p->next = alloc.allocate(1); *(p->next) = node<T>(pt->element);

                p = p->next; pt = pt->next;
            }
        } return *this;
    }

    template <typename T, typename Alloc>
    forward_list<T, Alloc>& forward_list<T, Alloc>::operator = (std::initializer_list<T> init)
    {
        if (!empty()) clear();

        auto p = ph; cnt = init.size();

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(*it);

            p = p->next;
        }
        return *this;
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::assign()
    {
        if (!empty()) clear();
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::assign(size_type count, const T& value)
    {
        if (!empty()) clear();

        auto p = ph; cnt = count;

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(value);

            p = p->next;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::assign(const forward_list& rhs)
    {
        if (!empty()) clear();

        auto p = ph, pt = rhs.data(0); cnt = rhs.size();

        for (size_t i = 0; i < cnt; ++i)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(pt->element);

            p = p->next; pt = pt->next;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::assign(std::initializer_list<T> init)
    {
        if (!empty()) clear();

        auto p = ph; cnt = init.size();

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            p->next = alloc.allocate(1); *(p->next) = node<T>(*it);

            p = p->next;
        }
    }

    template <typename T, typename Alloc>
    typename forward_list<T, Alloc>::pointer
    forward_list<T, Alloc>::data(size_type pos) noexcept
    {
        if (pos < 0) {
            return ph;
        } else if (pos >= cnt) {
            return nullptr;
        } else {
            auto p = ph->next;
            for (size_t i = 0; i < pos; ++i) {
                p = p->next;
            } return p;
        }
    }

    template <typename T, typename Alloc>
    typename forward_list<T, Alloc>::const_pointer
    forward_list<T, Alloc>::data(size_type pos) const noexcept
    {
        if (pos < 0) {
            return ph;
        } else if (pos >= cnt) {
            return nullptr;
        } else {
            auto p = ph->next;
            for (size_t i = 0; i < pos; ++i) {
                p = p->next;
            } return p;
        }
    }

    template <typename T, typename Alloc>
    typename forward_list<T, Alloc>::reference
    forward_list<T, Alloc>::operator [] (size_type pos)
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
    typename forward_list<T, Alloc>::const_reference
    forward_list<T, Alloc>::operator [] (size_type pos) const
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
    void forward_list<T, Alloc>::clear() noexcept
    {
        /* 保留头节点 */
        auto pt = ph->next; ph->next = nullptr;

        /* 销毁成员节点 */
        for ( ; cnt > 0; --cnt)
        {
            auto p = pt->next; alloc.deallocate(pt, 1); pt = p;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::insert(size_type pos, const T& value)
    {
        if (empty()) { assign(1, value); return; }

        auto p = alloc.allocate(1); *p = node<T>(value);

        auto pt = ph;

        if (pos < cnt)
        {
            for (size_t i = 0; i < pos; ++i) pt = pt->next;

            p->next = pt->next; pt->next = p; ++cnt;
        }
        else
        {
            for (size_t i = 0; i < cnt; ++i) pt = pt->next;

            pt->next = p; ++cnt;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::insert(size_type pos, size_type count, const T& value)
    {
        if (empty()) { assign(count, value); return; }

        if (pos < cnt) {
            for (size_t i = 0; i < count; ++i) insert(pos, value);
        } else {
            for (size_t i = 0; i < count; ++i) insert(cnt, value);
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::insert(size_type pos, const forward_list& rhs)
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
    void forward_list<T, Alloc>::insert(size_type pos, std::initializer_list<T> init)
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
    void forward_list<T, Alloc>::erase(size_type pos)
    {
        if (empty()) return;

        pointer p = ph, pt;

        if (pos < cnt - 1)
        {
            for (size_t i = 0; i < pos; ++i) p = p->next;

            pt = p->next; p->next = pt->next;

            alloc.deallocate(pt, 1); --cnt;
        }
        else if (pos == cnt - 1)
        {
            for (size_t i = 0; i < cnt - 1; ++i) p = p->next;

            alloc.deallocate(p->next, 1); p->next = nullptr; --cnt;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::erase(size_type lpos, size_type rpos)
    {
        if (lpos <= rpos)
        {
            if (lpos >= cnt) return;

            if (rpos >= cnt) rpos = cnt - 1;

            auto i = rpos - lpos + 1; while (i-- > 0) erase(lpos);
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::unique()
    {
        for (size_t i = 0; i + 1 < size(); )
        {
            if ((*this)[i] == (*this)[i + 1]) erase(i + 1); else ++i;
        }
    }

    template <typename T, typename Alloc>
    template <typename BinaryPredicate>
    void forward_list<T, Alloc>::unique(BinaryPredicate p)
    {
        for (size_t i = 0; i + 1 < size(); )
        {
            if (p((*this)[i], (*this)[i + 1])) erase(i + 1); else ++i;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::remove(const T& value)
    {
        for (size_t i = 0; i < size(); )
        {
            if ((*this)[i] == value) erase(i); else ++i;
        }
    }

    template <typename T, typename Alloc>
    template <typename UnaryPredicate>
    void forward_list<T, Alloc>::remove_if(UnaryPredicate p)
    {
        for (size_t i = 0; i < size(); )
        {
            if (p((*this)[i])) erase(i); else ++i;
        }
    }

    template <typename T, typename Alloc>
    void forward_list<T, Alloc>::reverse() noexcept
    {
        pointer p = ph->next, pt;

        alloc.deallocate(ph, 1); ph = nullptr;

        for (size_t i = 0; i < cnt; ++i) {
            pt = p; p = p->next; pt->next = ph; ph = pt;
        } ph = alloc.allocate(1); *ph = node<T>(); ph->next = pt;
    }
}

#endif // FORWARD_LIST_H
