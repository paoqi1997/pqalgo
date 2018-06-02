#ifndef STACK_H
#define STACK_H

#include <memory>
#include <utility>

#include "bases/list.h"

namespace pits
{
    template <typename T, typename Container> class stack;

    template <typename T, typename Container>
    bool operator == (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() == rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator != (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() != rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator <  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() <  rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator <= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() <= rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator >  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() >  rhs.get_container();
    }

    template <typename T, typename Container>
    bool operator >= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs.get_container() >= rhs.get_container();
    }

    template <typename T, typename Container>
    void swap(stack<T, Container>& lhs, stack<T, Container>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Container = pits::list<T>>
    class stack
    {
    public:
        using value_type      = typename Container::value_type;
        using size_type       = typename Container::size_type;
        using difference_type = typename Container::difference_type;

        using reference       = typename Container::reference;
        using const_reference = typename Container::const_reference;

        using container_type  = Container;

        stack();
        stack(const stack&);

        ~stack();

        stack& operator = (const stack&);

        reference top() { return c.back(); }
        const_reference top() const { return c.back(); }

        container_type get_container() const { return c; }

        void push(const T& value) { c.push_back(value); }

        template <typename... Args>
        void emplace(Args&&... args)
        { c.emplace_back(std::forward<Args>(args)...); }

        void pop() { c.pop_back(); }

        size_type size() const { return c.size(); }

        bool empty() const { return c.empty(); }

        void swap(stack& rhs) noexcept { std::swap(*this, rhs); }
    private:
        Container c;
    };

    template <typename T, typename Container>
    stack<T, Container>::stack()
    {
        // nothing
    }

    template <typename T, typename Container>
    stack<T, Container>::stack(const stack& rhs)
    {
        c = rhs.get_container();
    }

    template <typename T, typename Container>
    stack<T, Container>::~stack()
    {
        // nothing
    }

    template <typename T, typename Container>
    stack<T, Container>& stack<T, Container>::operator = (const stack& rhs)
    {
        if (this != &rhs) c = rhs.get_container();
    }
}

#endif // STACK_H
