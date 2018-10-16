#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <utility>

#include "../bases/list.h"

namespace pits
{
    template <typename T, typename Container> class queue;

    template <typename T, typename Container>
    bool operator == (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() == rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator != (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() != rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator <  (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() <  rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator <= (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() <= rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator >  (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() >  rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator >= (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs.get_container() >= rhs.get_container();
    }

    template <typename T, typename Container>
    void swap(queue<T, Container>& lhs, queue<T, Container>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Container = pits::list<T>>
    class queue
    {
    public:
        using value_type      = typename Container::value_type;
        using size_type       = typename Container::size_type;

        using reference       = typename Container::reference;
        using const_reference = typename Container::const_reference;

        using container_type  = Container;

        queue();
        queue(const queue&);

        ~queue();

        queue& operator = (const queue&);

        reference front() { return c.front(); }
        const_reference front() const { return c.front(); }

        reference back() { return c.back(); }
        const_reference back() const { return c.back(); }

        container_type get_container() const { return c; }

        void push(const T& value) { c.push_back(value); }

        template <typename... Args>
        void emplace(Args&&... args)
        { c.emplace_back(std::forward<Args>(args)...); }

        void pop() { c.pop_front(); }

        size_type size() const { return c.size(); }

        bool empty() const { return c.empty(); }

        void swap(queue& rhs) noexcept { std::swap(*this, rhs); }
    private:
        Container c;
    };

    template <typename T, typename Container>
    queue<T, Container>::queue()
    {
        // nothing
    }

    template <typename T, typename Container>
    queue<T, Container>::queue(const queue& rhs)
    {
        c = rhs.get_container();
    }

    template <typename T, typename Container>
    queue<T, Container>::~queue()
    {
        // nothing
    }

    template <typename T, typename Container>
    queue<T, Container>& queue<T, Container>::operator = (const queue& rhs)
    {
        if (this != &rhs) c = rhs.get_container();
    }
}

#endif // QUEUE_H
