#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <utility>

namespace pits
{
    template <typename I>
    struct iterator_traits
    {
        using value_type      = typename I::value_type;
        using difference_type = typename I::difference_type;
        using pointer         = typename I::pointer;
        using reference       = typename I::reference;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
        using value_type      = T;
        using difference_type = ptrdiff_t;
        using pointer         = T*;
        using reference       = T&;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        using value_type      = T;
        using difference_type = ptrdiff_t;
        using pointer         = const T*;
        using reference       = const T&;
    };

    template <typename InputIt, typename Distance>
    void advance(InputIt& it, Distance n) { it += n; }

    template <typename InputIt>
    typename iterator_traits<InputIt>::difference_type
    distance(InputIt first, InputIt last) { return last - first; }

    template <typename BidirIt>
    BidirIt prev(BidirIt it,
        typename iterator_traits<BidirIt>::difference_type n = 1)
    {
        advance(it, -n); return it;
    }

    template <typename ForwardIt>
    ForwardIt next(ForwardIt it,
        typename iterator_traits<ForwardIt>::difference_type n = 1)
    {
        advance(it, +n); return it;
    }

    template <typename Iterator> class be_reverse_it;

    // pits::begin及pits::cbegin
    template <typename C>
    auto begin(C& c) -> decltype(c.begin()) { return c.begin(); }

    template <typename C>
    auto begin(const C& c) -> decltype(c.begin()) { return c.begin(); }

    template <typename T, size_t N>
    T* begin(T(&array)[N]) noexcept { return array; }

    template <typename C>
    auto cbegin(const C& c) noexcept -> decltype(begin(c)) { return begin(c); }

    // pits::end及pits::cend
    template <typename C>
    auto end(C& c) -> decltype(c.end()) { return c.end(); }

    template <typename C>
    auto end(const C& c) -> decltype(c.end()) { return c.end(); }

    template <typename T, size_t N>
    T* end(T(&array)[N]) noexcept { return array + N; }

    template <typename C>
    auto cend(const C& c) noexcept -> decltype(end(c)) { return end(c); }

    // pits::rbegin及pits::crbegin
    template <typename C>
    auto rbegin(C& c) -> decltype(c.rbegin()) { return c.rbegin(); }

    template <typename C>
    auto rbegin(const C& c) -> decltype(c.rbegin()) { return c.rbegin(); }

    template <typename T, size_t N>
    be_reverse_it<T*> rbegin(T(&array)[N]) noexcept { return array + N - 1; }

    template <typename C>
    auto crbegin(const C& c) noexcept -> decltype(rbegin(c)) { return rbegin(c); }

    // pits::rend及pits::crend
    template <typename C>
    auto rend(C& c) -> decltype(c.rend()) { return c.rend(); }

    template <typename C>
    auto rend(const C& c) -> decltype(c.rend()) { return c.rend(); }

    template <typename T, size_t N>
    be_reverse_it<T*> rend(T(&array)[N]) noexcept { return array - 1; }

    template <typename C>
    auto crend(const C& c) noexcept -> decltype(rend(c)) { return rend(c); }

    // pits::size
    template <typename C>
    auto size(const C& c) -> decltype(c.size()) { return c.size(); }

    template <typename T, size_t N>
    size_t size(const T(&array)[N]) noexcept { return N; }

    // pits::empty
    template <typename C>
    auto empty(const C& c) -> decltype(c.empty()) { return c.empty(); }

    template <typename T, size_t N>
    bool empty(const T(&array)[N]) noexcept { return false; }

    template <typename T>
    bool empty(std::initializer_list<T> init) noexcept { return init.size() == 0; }

    // pits::data
    template <typename C>
    auto data(C& c) -> decltype(c.data()) { return c.data(); }

    template <typename C>
    auto data(const C& c) -> decltype(c.data()) { return c.data(); }

    template <typename T, size_t N>
    T* data(T(&array)[N]) noexcept { return array; }

    template <typename T>
    const T* data(std::initializer_list<T> init) noexcept { return init.begin(); }

    template <typename Iterator>
    be_reverse_it<Iterator> make_reverse_iterator(Iterator it)
    {
        return be_reverse_it<Iterator>(it);
    }

    template <typename Is, typename It>
    bool operator == (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Is, typename It>
    bool operator != (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Is, typename It>
    bool operator <  (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() >  rhs.base();
    }

    template <typename Is, typename It>
    bool operator <= (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Is, typename It>
    bool operator >  (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() <  rhs.base();
    }

    template <typename Is, typename It>
    bool operator >= (const be_reverse_it<Is>& lhs, const be_reverse_it<It>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename It>
    be_reverse_it<It> operator +
        (typename be_reverse_it<It>::difference_type n, const be_reverse_it<It>& rhs)
    {
        return rhs + n;
    }

    template <typename Is, typename It>
    auto operator - (const be_reverse_it<Is>& lhs,
                     const be_reverse_it<It>& rhs) -> decltype(rhs.base() - lhs.base())
    {
        return rhs.base() - lhs.base();
    }

    template <typename Iterator>
    class be_reverse_it
    {
    public:
        using iterator_type   = Iterator;

        using value_type      = typename iterator_traits<Iterator>::value_type;
        using difference_type = typename iterator_traits<Iterator>::difference_type;

        using pointer         = typename iterator_traits<Iterator>::pointer;
        using reference       = typename iterator_traits<Iterator>::reference;

        be_reverse_it() = default;

        be_reverse_it(const Iterator& rt) { it = rt; }

        template <typename U>
        be_reverse_it(const be_reverse_it<U>& rhs) { it = rhs.it; }

        be_reverse_it& operator = (const Iterator& rt) { it = rt; return *this; }

        template <typename U>
        be_reverse_it& operator = (const be_reverse_it<U>& rhs) { it = rhs.it; return *this; }

        Iterator base() const { return it; }

        pointer operator -> () const { return it; }
        reference operator * () const { return *it; }

        reference operator [] (difference_type n) const { return *(it - n); }

        be_reverse_it& operator ++ () { --it; return *this; }
        be_reverse_it& operator -- () { ++it; return *this; }

        be_reverse_it operator ++ (int)
        {
            auto rhs = *this; --it; return rhs;
        }
        be_reverse_it operator -- (int)
        {
            auto rhs = *this; ++it; return rhs;
        }

        be_reverse_it operator + (difference_type n) const
        {
            return be_reverse_it<Iterator>(it - n);
        }
        be_reverse_it operator - (difference_type n) const
        {
            return be_reverse_it<Iterator>(it + n);
        }

        be_reverse_it& operator += (difference_type n) { it -= n; return *this; }
        be_reverse_it& operator -= (difference_type n) { it += n; return *this; }
    private:
        Iterator it;
    };
}

#endif // ITERATOR_H
