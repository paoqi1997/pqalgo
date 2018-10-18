#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <memory>
#include <utility>

#include "../containers/queue.h"

namespace pits
{
    template <typename T>
    struct tnode
    {
        T element; tnode<T> *leftchild, *rightchild;

        tnode() : leftchild(nullptr), rightchild(nullptr) {}

        tnode(const T& _element) : element(_element), leftchild(nullptr), rightchild(nullptr) {}
    };

    /* 前序遍历 */
    template <typename T>
    inline void preorder(const tnode<T> *p)
    {
        if (p != nullptr)
        {
            std::cout << p->element << ' ';

            preorder(p->leftchild);

            preorder(p->rightchild);
        }
    }

    /* 中序遍历 */
    template <typename T>
    inline void inorder(const tnode<T> *p)
    {
        if (p != nullptr)
        {
            inorder(p->leftchild);

            std::cout << p->element << ' ';

            inorder(p->rightchild);
        }
    }

    /* 后序遍历 */
    template <typename T>
    inline void postorder(const tnode<T> *p)
    {
        if (p != nullptr)
        {
            postorder(p->leftchild);

            postorder(p->rightchild);

            std::cout << p->element << ' ';
        }
    }

    /* 层次遍历 */
    template <typename T>
    inline void levelorder(const tnode<T> *p)
    {
        queue<tnode<T>*> pool;

        while (p != nullptr)
        {
            std::cout << p->element << ' ';

            if (p->leftchild != nullptr)
            {
                pool.push(p->leftchild);
            }
            if (p->rightchild != nullptr)
            {
                pool.push(p->rightchild);
            }

            if (pool.empty()) {
                break;
            } else {
                p = pool.front(); pool.pop();
            }
        }
    }

    template <typename T, typename Alloc> class binarytree;

    template <typename T, typename Alloc>
    int binarytree_compare
    (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        auto box1 = lhs.get_tnodes(), box2 = rhs.get_tnodes();

        while (!box1.empty() && !box2.empty())
        {
            if (box1.front()->element != box2.front()->element)
            {
                return box1.front()->element - box2.front()->element;
            }
            box1.pop(), box2.pop();
        }
        return lhs.size() - rhs.size();
    }

    template <typename T, typename Alloc>
    bool operator == (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) == 0;
    }

    template <typename T, typename Alloc>
    bool operator != (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) != 0;
    }

    template <typename T, typename Alloc>
    bool operator <  (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) <  0;
    }

    template <typename T, typename Alloc>
    bool operator <= (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) <= 0;
    }

    template <typename T, typename Alloc>
    bool operator >  (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) >  0;
    }

    template <typename T, typename Alloc>
    bool operator >= (const binarytree<T, Alloc>& lhs, const binarytree<T, Alloc>& rhs)
    {
        return binarytree_compare(lhs, rhs) >= 0;
    }

    template <typename T, typename Alloc>
    void swap(binarytree<T, Alloc>& lhs, binarytree<T, Alloc>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Alloc = std::allocator<T>>
    class binarytree
    {
    public:
        using value_type      = T;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;

        using pointer         = tnode<T>*;
        using const_pointer   = const tnode<T>*;

        using reference       = T&;
        using const_reference = const T&;

        using allocator_type  = typename Alloc::template rebind<tnode<T>>::other;

        binarytree();
        binarytree(const T&);
        binarytree(size_type, const T&);
        binarytree(const binarytree&);
        binarytree(std::initializer_list<T>);

        ~binarytree() { deletetree(root); }

        binarytree& operator = (const binarytree&);
        binarytree& operator = (std::initializer_list<T>);

        void assign();
        void assign(const T&);
        void assign(size_type, const T&);
        void assign(const binarytree&);
        void assign(std::initializer_list<T>);

        pointer data(size_type) noexcept;
        const_pointer data(size_type) const noexcept;

        reference at(size_type pos) { return data(pos)->element; }
        const_reference at(size_type pos) const { return data(pos)->element; }

        reference operator [] (size_type pos) { return data(pos)->element; }
        const_reference operator [] (size_type pos) const { return data(pos)->element; }

        size_type height() const;
        size_type degree(size_type) const;

        queue<pointer> get_tnodes() const;

        const_pointer get_root() const { return root; }

        allocator_type get_allocator() const { return alloc; }

        void clear() noexcept;

        void output(void(*)(const_pointer)) noexcept;

        size_type size() const noexcept { return cnt; }

        bool empty() const noexcept { return cnt == 0; }

        void swap(binarytree& rhs) noexcept { std::swap(*this, rhs); }
    private:
        size_type height(pointer) const;

        void deletetree(pointer) noexcept;

        pointer root; size_type cnt; allocator_type alloc;
    };

    template <typename T, typename Alloc>
    binarytree<T, Alloc>::binarytree() : cnt(0)
    {
        root = nullptr;
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>::binarytree(const T& value) : cnt(1)
    {
        root = alloc.allocate(1); *root = tnode<T>(value);
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>::binarytree(size_type count, const T& value) : cnt(count)
    {
        root = alloc.allocate(1); *root = tnode<T>(value);

        auto p = root; queue<pointer> pool; size_t flag = 0;

        for (size_t i = 1; i < cnt; )
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (i < cnt && p->leftchild == nullptr)
            {
                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(value);

                pool.push(p->leftchild);

                ++flag, ++i;
            }
            if (i < cnt && p->rightchild == nullptr)
            {
                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(value);

                pool.push(p->rightchild);

                ++flag, ++i;
            }
        }
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>::binarytree(const binarytree& rhs) : cnt(rhs.size())
    {
        root = alloc.allocate(1); *root = tnode<T>(rhs.at(0));

        auto box = rhs.get_tnodes(); box.pop();

        auto p = root; queue<pointer> pool; size_t flag = 0;

        while (!box.empty())
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (!box.empty() && p->leftchild == nullptr)
            {
                auto t = box.front()->element; box.pop();

                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(t);

                pool.push(p->leftchild);

                ++flag;
            }
            if (!box.empty() && p->rightchild == nullptr)
            {
                auto t = box.front()->element; box.pop();

                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(t);

                pool.push(p->rightchild);

                ++flag;
            }
        }
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>::binarytree(std::initializer_list<T> init) : cnt(init.size())
    {
        root = alloc.allocate(1); *root = tnode<T>(*(init.begin()));

        auto p = root; queue<pointer> pool; size_t flag = 0;

        for (auto it = init.begin() + 1; it != init.end(); )
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (it != init.end() && p->leftchild == nullptr)
            {
                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(*it);

                pool.push(p->leftchild);

                ++flag, ++it;
            }
            if (it != init.end() && p->rightchild == nullptr)
            {
                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(*it);

                pool.push(p->rightchild);

                ++flag, ++it;
            }
        }
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>& binarytree<T, Alloc>::operator = (const binarytree& rhs)
    {
        if (this != &rhs)
        {
            if (!empty()) clear();

            root = alloc.allocate(1); *root = tnode<T>(rhs.at(0));

            cnt = rhs.size();

            auto box = rhs.get_tnodes(); box.pop();

            auto p = root; queue<pointer> pool; size_t flag = 0;

            while (!box.empty())
            {
                if (flag == 2)
                {
                    p = pool.front(); pool.pop();

                    flag = 0;
                }
                if (!box.empty() && p->leftchild == nullptr)
                {
                    auto t = box.front()->element; box.pop();

                    p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(t);

                    pool.push(p->leftchild);

                    ++flag;
                }
                if (!box.empty() && p->rightchild == nullptr)
                {
                    auto t = box.front()->element; box.pop();

                    p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(t);

                    pool.push(p->rightchild);

                    ++flag;
                }
            }
        } return *this;
    }

    template <typename T, typename Alloc>
    binarytree<T, Alloc>& binarytree<T, Alloc>::operator = (std::initializer_list<T> init)
    {
        if (!empty()) clear();

        root = alloc.allocate(1); *root = tnode<T>(*(init.begin()));

        cnt = init.size();

        auto p = root; queue<pointer> pool; size_t flag = 0;

        for (auto it = init.begin() + 1; it != init.end(); )
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (it != init.end() && p->leftchild == nullptr)
            {
                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(*it);

                pool.push(p->leftchild);

                ++flag, ++it;
            }
            if (it != init.end() && p->rightchild == nullptr)
            {
                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(*it);

                pool.push(p->rightchild);

                ++flag, ++it;
            }
        } return *this;
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::assign()
    {
        if (!empty()) clear();
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::assign(const T& value)
    {
        if (!empty()) clear();

        root = alloc.allocate(1); *root = tnode<T>(value);

        cnt = 1;
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::assign(size_type count, const T& value)
    {
        if (!empty()) clear();

        root = alloc.allocate(1); *root = tnode<T>(value);

        cnt = count;

        auto p = root; queue<pointer> pool; size_t flag = 0;

        for (size_t i = 1; i < cnt; )
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (i < cnt && p->leftchild == nullptr)
            {
                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(value);

                pool.push(p->leftchild);

                ++flag, ++i;
            }
            if (i < cnt && p->rightchild == nullptr)
            {
                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(value);

                pool.push(p->rightchild);

                ++flag, ++i;
            }
        }
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::assign(const binarytree& rhs)
    {
        if (!empty()) clear();

        root = alloc.allocate(1); *root = tnode<T>(rhs.at(0));

        cnt = rhs.size();

        auto box = rhs.get_tnodes(); box.pop();

        auto p = root; queue<pointer> pool; size_t flag = 0;

        while (!box.empty())
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (!box.empty() && p->leftchild == nullptr)
            {
                auto t = box.front()->element; box.pop();

                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(t);

                pool.push(p->leftchild);

                ++flag;
            }
            if (!box.empty() && p->rightchild == nullptr)
            {
                auto t = box.front()->element; box.pop();

                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(t);

                pool.push(p->rightchild);

                ++flag;
            }
        }
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::assign(std::initializer_list<T> init)
    {
        if (!empty()) clear();

        root = alloc.allocate(1); *root = tnode<T>(*(init.begin()));

        cnt = init.size();

        auto p = root; queue<pointer> pool; size_t flag = 0;

        for (auto it = init.begin() + 1; it != init.end(); )
        {
            if (flag == 2)
            {
                p = pool.front(); pool.pop();

                flag = 0;
            }
            if (it != init.end() && p->leftchild == nullptr)
            {
                p->leftchild = alloc.allocate(1); *(p->leftchild) = tnode<T>(*it);

                pool.push(p->leftchild);

                ++flag, ++it;
            }
            if (it != init.end() && p->rightchild == nullptr)
            {
                p->rightchild = alloc.allocate(1); *(p->rightchild) = tnode<T>(*it);

                pool.push(p->rightchild);

                ++flag, ++it;
            }
        }
    }

    template <typename T, typename Alloc>
    typename binarytree<T, Alloc>::pointer
    binarytree<T, Alloc>::data(size_type pos) noexcept
    {
        if (pos < 0) pos = 0;

        else if (pos >= cnt) pos = cnt - 1;

        auto box = get_tnodes();

        for (size_t i = 0; i < pos; ++i)
        {
            box.pop();
        }
        return box.front();
    }

    template <typename T, typename Alloc>
    typename binarytree<T, Alloc>::const_pointer
    binarytree<T, Alloc>::data(size_type pos) const noexcept
    {
        if (pos < 0) pos = 0;

        else if (pos >= cnt) pos = cnt - 1;

        auto box = get_tnodes();

        for (size_t i = 0; i < pos; ++i)
        {
            box.pop();
        }
        return box.front();
    }

    template <typename T, typename Alloc>
    typename binarytree<T, Alloc>::size_type
    binarytree<T, Alloc>::height() const
    {
        return height(root);
    }

    template <typename T, typename Alloc>
    typename binarytree<T, Alloc>::size_type
    binarytree<T, Alloc>::degree(size_type pos) const
    {
        auto p = data(pos); size_t n = 0;

        if (p->leftchild != nullptr)
        {
            ++n;
        }
        if (p->rightchild != nullptr)
        {
            ++n;
        }
        return n;
    }

    template <typename T, typename Alloc>
    queue<tnode<T>*> binarytree<T, Alloc>::get_tnodes() const
    {
        auto p = root; queue<pointer> box, pool;

        while (p != nullptr)
        {
            box.push(p);

            if (p->leftchild != nullptr)
            {
                pool.push(p->leftchild);
            }
            if (p->rightchild != nullptr)
            {
                pool.push(p->rightchild);
            }

            if (pool.empty()) {
                break;
            } else {
                p = pool.front(); pool.pop();
            }
        } return box;
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::clear() noexcept
    {
        /* 不保留根节点 */
        deletetree(root); root = nullptr;
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::output(void(*func)(const_pointer)) noexcept
    {
        func(root); std::cout << std::endl;
    }

    template <typename T, typename Alloc>
    typename binarytree<T, Alloc>::size_type
    binarytree<T, Alloc>::height(pointer p) const
    {
        if (p == nullptr) return 0;     // 空树

        int hl = height(p->leftchild);  // 左子树

        int hr = height(p->rightchild); // 右子树

        return (hl > hr) ? ++hl : ++hr;
    }

    template <typename T, typename Alloc>
    void binarytree<T, Alloc>::deletetree(pointer p) noexcept
    {
        if (p != nullptr)
        {
            deletetree(p->leftchild);

            deletetree(p->rightchild);

            alloc.deallocate(p, 1); --cnt;
        }
    }
}

#endif // BINARYTREE_H
