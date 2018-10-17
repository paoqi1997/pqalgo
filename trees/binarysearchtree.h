#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <memory>
#include <utility>

#include "../containers/queue.h"

namespace pits
{
    template <typename T>
    struct bstnode
    {
        T element; bstnode<T> *leftchild, *rightchild;

        bstnode() : leftchild(nullptr), rightchild(nullptr) {}

        bstnode(const T& _element) : element(_element), leftchild(nullptr), rightchild(nullptr) {}
    };

    /* 前序遍历 */
    template <typename T>
    inline void preorder(const bstnode<T> *p)
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
    inline void inorder(const bstnode<T> *p)
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
    inline void postorder(const bstnode<T> *p)
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
    inline void levelorder(const bstnode<T> *p)
    {
        queue<bstnode<T>*> pool;

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

    template <typename T, typename Alloc> class binarysearchtree;

    template <typename T, typename Alloc>
    int binarysearchtree_compare
    (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        auto box1 = lhs.get_bstnodes(), box2 = rhs.get_bstnodes();

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
    bool operator == (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) == 0;
    }

    template <typename T, typename Alloc>
    bool operator != (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) != 0;
    }

    template <typename T, typename Alloc>
    bool operator <  (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) <  0;
    }

    template <typename T, typename Alloc>
    bool operator <= (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) <= 0;
    }

    template <typename T, typename Alloc>
    bool operator >  (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) >  0;
    }

    template <typename T, typename Alloc>
    bool operator >= (const binarysearchtree<T, Alloc>& lhs, const binarysearchtree<T, Alloc>& rhs)
    {
        return binarysearchtree_compare(lhs, rhs) >= 0;
    }

    template <typename T, typename Alloc>
    void swap(binarysearchtree<T, Alloc>& lhs, binarysearchtree<T, Alloc>& rhs) noexcept { lhs.swap(rhs); }

    template <typename T, typename Alloc = std::allocator<T>>
    class binarysearchtree
    {
    public:
        using value_type      = T;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;

        using pointer         = bstnode<T>*;
        using const_pointer   = const bstnode<T>*;

        using reference       = T&;
        using const_reference = const T&;

        using allocator_type  = typename Alloc::template rebind<bstnode<T>>::other;

        binarysearchtree();
        binarysearchtree(const T&);
        binarysearchtree(const binarysearchtree&);
        binarysearchtree(std::initializer_list<T>);

        ~binarysearchtree() { deletetree(root); }

        binarysearchtree& operator = (const binarysearchtree&);
        binarysearchtree& operator = (std::initializer_list<T>);

        void assign();
        void assign(const T&);
        void assign(const binarysearchtree&);
        void assign(std::initializer_list<T>);

        pointer data(size_type) noexcept;
        const_pointer data(size_type) const noexcept;

        reference at(size_type pos) { return data(pos)->element; }
        const_reference at(size_type pos) const { return data(pos)->element; }

        reference operator [] (size_type pos) { return data(pos)->element; }
        const_reference operator [] (size_type pos) const { return data(pos)->element; }

        size_type level(size_type) const;

        size_type height() const;
        size_type degree(size_type) const;

        queue<pointer> get_bstnodes() const;

        const_pointer get_root() const { return root; }

        allocator_type get_allocator() const { return alloc; }

        bool find(const T&);

        void clear() noexcept;

        void insert(const T&);
        void insert(const binarysearchtree&);
        void insert(std::initializer_list<T>);

        void erase(const T&);

        void output(void(*)(const_pointer)) noexcept;

        size_type size() const noexcept { return cnt; }

        bool empty() const noexcept { return cnt == 0; }

        void swap(binarysearchtree& rhs) noexcept { std::swap(*this, rhs); }
    private:
        pointer root; size_type cnt; allocator_type alloc;

        size_type height(pointer) const;

        void deletetree(pointer) noexcept;

        size_type level(pointer, const_pointer, size_type) const;
    };

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>::binarysearchtree() : cnt(0)
    {
        root = nullptr;
    }

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>::binarysearchtree(const T& value) : cnt(1)
    {
        root = alloc.allocate(1); *root = bstnode<T>(value);
    }

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>::binarysearchtree(const binarysearchtree& rhs) : cnt(0)
    {
        auto box = rhs.get_bstnodes();

        if (box.empty()) {
            root = nullptr;
        } else {
            root = alloc.allocate(1); *root = bstnode<T>(rhs.at(0));
            ++cnt; box.pop();
        }

        while (!box.empty())
        {
            pointer p = root, pt, pu = box.front();

            while (p != nullptr)
            {
                pt = p;

                if (pu->element < p->element) {
                    p = p->leftchild;
                } else if (pu->element > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (pu->element < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else if (pu->element > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else
            {
                box.pop();
            }
        }
    }

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>::binarysearchtree(std::initializer_list<T> init) : cnt(0)
    {
        if (init.begin() == init.end()) {
            root = nullptr;
        } else {
            root = alloc.allocate(1); *root = bstnode<T>(*(init.begin()));
            ++cnt;
        }

        for (auto it = init.begin() + 1; it != init.end(); ++it)
        {
            pointer p = root, pt;

            while (p != nullptr)
            {
                pt = p;

                if (*it < p->element) {
                    p = p->leftchild;
                } else if (*it > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (*it < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(*it);
                ++cnt;
            }
            else if (*it > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(*it);
                ++cnt;
            }
        }
    }

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>& binarysearchtree<T, Alloc>::operator = (const binarysearchtree& rhs)
    {
        if (this != &rhs)
        {
            if (!empty()) clear();

            auto box = rhs.get_bstnodes();

            if (box.empty()) {
                root = nullptr;
            } else {
                root = alloc.allocate(1); *root = bstnode<T>(rhs.at(0));
                ++cnt; box.pop();
            }

            while (!box.empty())
            {
                pointer p = root, pt, pu = box.front();

                while (p != nullptr)
                {
                    pt = p;

                    if (pu->element < p->element) {
                        p = p->leftchild;
                    } else if (pu->element > p->element) {
                        p = p->rightchild;
                    } else {
                        break;
                    }
                }

                if (pu->element < pt->element)
                {
                    pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(pu->element);
                    ++cnt; box.pop();
                }
                else if (pu->element > pt->element)
                {
                    pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(pu->element);
                    ++cnt; box.pop();
                }
                else
                {
                    box.pop();
                }
            }
        } return *this;
    }

    template <typename T, typename Alloc>
    binarysearchtree<T, Alloc>& binarysearchtree<T, Alloc>::operator = (std::initializer_list<T> init)
    {
        if (!empty()) clear();

        if (init.begin() == init.end()) {
            root = nullptr;
        } else {
            root = alloc.allocate(1); *root = bstnode<T>(*(init.begin()));
            ++cnt;
        }

        for (auto it = init.begin() + 1; it != init.end(); ++it)
        {
            pointer p = root, pt;

            while (p != nullptr)
            {
                pt = p;

                if (*it < p->element) {
                    p = p->leftchild;
                } else if (*it > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (*it < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(*it);
                ++cnt;
            }
            else if (*it > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(*it);
                ++cnt;
            }
        } return *this;
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::assign()
    {
        if (!empty()) clear();
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::assign(const T& value)
    {
        if (!empty()) clear();

        cnt = 1;

        root = alloc.allocate(1); *root = bstnode<T>(value);
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::assign(const binarysearchtree& rhs)
    {
        if (!empty()) clear();

        cnt = 0;

        auto box = rhs.get_bstnodes();

        if (box.empty()) {
            root = nullptr;
        } else {
            root = alloc.allocate(1); *root = bstnode<T>(rhs.at(0));
            ++cnt; box.pop();
        }

        while (!box.empty())
        {
            pointer p = root, pt, pu = box.front();

            while (p != nullptr)
            {
                pt = p;

                if (pu->element < p->element) {
                    p = p->leftchild;
                } else if (pu->element > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (pu->element < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else if (pu->element > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else
            {
                box.pop();
            }
        }
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::assign(std::initializer_list<T> init)
    {
        if (!empty()) clear();

        cnt = 0;

        if (init.begin() == init.end()) {
            root = nullptr;
        } else {
            root = alloc.allocate(1); *root = bstnode<T>(*(init.begin()));
            ++cnt;
        }

        for (auto it = init.begin() + 1; it != init.end(); ++it)
        {
            pointer p = root, pt;

            while (p != nullptr)
            {
                pt = p;

                if (*it < p->element) {
                    p = p->leftchild;
                } else if (*it > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (*it < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(*it);
                ++cnt;
            }
            else if (*it > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(*it);
                ++cnt;
            }
        }
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::pointer
    binarysearchtree<T, Alloc>::data(size_type pos) noexcept
    {
        if (pos < 0) pos = 0;

        else if (pos >= cnt) pos = cnt - 1;

        auto box = get_bstnodes();

        for (size_t i = 0; i < pos; ++i)
        {
            box.pop();
        }
        return box.front();
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::const_pointer
    binarysearchtree<T, Alloc>::data(size_type pos) const noexcept
    {
        if (pos < 0) pos = 0;

        else if (pos >= cnt) pos = cnt - 1;

        auto box = get_bstnodes();

        for (size_t i = 0; i < pos; ++i)
        {
            box.pop();
        }
        return box.front();
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::size_type
    binarysearchtree<T, Alloc>::level(size_type pos) const
    {
        if (pos < 0) pos = 0;

        else if (pos >= cnt) pos = cnt - 1;

        return level(root, this->data(pos), 1);
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::size_type
    binarysearchtree<T, Alloc>::height() const
    {
        return height(root);
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::size_type
    binarysearchtree<T, Alloc>::degree(size_type pos) const
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
    queue<bstnode<T>*> binarysearchtree<T, Alloc>::get_bstnodes() const
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
    bool binarysearchtree<T, Alloc>::find(const T& value)
    {
        pointer p = root;

        while (p != nullptr)
        {
            if (value < p->element)
            {
                p = p->leftchild;
            }
            else if (value > p->element)
            {
                p = p->rightchild;
            }
            else
            {
                return true;
            }
        } return false;
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::clear() noexcept
    {
        /* 不保留根节点 */
        deletetree(root); root = nullptr;
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::insert(const T& value)
    {
        if (empty()) { assign(value); return; }

        pointer p = root, pt;

        while (p != nullptr)
        {
            pt = p;

            if (value < p->element) {
                p = p->leftchild;
            } else if (value > p->element) {
                p = p->rightchild;
            } else {
                break;
            }
        }

        if (value < pt->element)
        {
            pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(value);
            ++cnt;
        }
        else if (value > pt->element)
        {
            pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(value);
            ++cnt;
        }
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::insert(const binarysearchtree& rhs)
    {
        if (empty()) { assign(rhs); return; }

        auto box = rhs.get_bstnodes();

        while (!box.empty())
        {
            pointer p = root, pt, pu = box.front();

            while (p != nullptr)
            {
                pt = p;

                if (pu->element < p->element) {
                    p = p->leftchild;
                } else if (pu->element > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (pu->element < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else if (pu->element > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(pu->element);
                ++cnt; box.pop();
            }
            else
            {
                box.pop();
            }
        }
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::insert(std::initializer_list<T> init)
    {
        if (empty()) { assign(init); return; }

        for (auto it = init.begin(); it != init.end(); ++it)
        {
            pointer p = root, pt;

            while (p != nullptr)
            {
                pt = p;

                if (*it < p->element) {
                    p = p->leftchild;
                } else if (*it > p->element) {
                    p = p->rightchild;
                } else {
                    break;
                }
            }

            if (*it < pt->element)
            {
                pt->leftchild = alloc.allocate(1); *(pt->leftchild) = bstnode<T>(*it);
                ++cnt;
            }
            else if (*it > pt->element)
            {
                pt->rightchild = alloc.allocate(1); *(pt->rightchild) = bstnode<T>(*it);
                ++cnt;
            }
        }
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::erase(const T& value)
    {
        pointer p = root, pt = nullptr;

        /* 寻找待删节点 */
        while (p != nullptr && value != p->element)
        {
            pt = p;

            if (value < p->element)
            {
                p = p->leftchild;
            }
            else
            {
                p = p->rightchild;
            }
        }

        if (p == nullptr) return;

        /* 存在两个叶子节点 */
        if (p->leftchild != nullptr && p->rightchild != nullptr)
        {
            /* 进入待删节点的左子树 */
            pointer pp = p->leftchild, pq = p;

            /* 寻找候补节点 */
            while (pp->rightchild != nullptr)
            {
                pq = pp; pp = pp->rightchild;
            }

            /* 建立过渡节点并处理叶子节点的连接关系 */
            auto pr = alloc.allocate(1); pr->element = pp->element;

            pr->leftchild = p->leftchild; pr->rightchild = p->rightchild;

            /* 处理父节点的连接关系 */
            if (pt == nullptr)
            {
                root = pr;
            }
            else if (p == pt->leftchild)
            {
                pt->leftchild = pr;
            }
            else
            {
                pt->rightchild = pr;
            }

            /* 取得候补节点的父节点 */
            pt = (p == pq) ? pr : pq;

            /* 删除待删节点，候补节点成为下一个待删节点 */
            alloc.deallocate(p, 1); p = pp;
        }

        /* 最多一个叶子节点 */
        pointer ps = nullptr;

        /* 取得叶子节点 */
        if (p->leftchild != nullptr)
        {
            ps = p->leftchild;
        }
        else
        {
            ps = p->rightchild;
        }

        /* 待删节点为根节点 */
        if (p == root)
        {
            root = ps;
        }
        else
        {
            /* 连接叶子节点 */
            if (p == pt->leftchild)
            {
                pt->leftchild = ps;
            }
            else
            {
                pt->rightchild = ps;
            }
        }
        /* 删除待删节点 */
        --cnt; alloc.deallocate(p, 1);
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::output(void(*func)(const_pointer)) noexcept
    {
        func(root); std::cout << std::endl;
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::size_type
    binarysearchtree<T, Alloc>::height(pointer p) const
    {
        if (p == nullptr) return 0;     // 空树

        int hl = height(p->leftchild);  // 左子树

        int hr = height(p->rightchild); // 右子树

        return (hl > hr) ? ++hl : ++hr;
    }

    template <typename T, typename Alloc>
    void binarysearchtree<T, Alloc>::deletetree(pointer p) noexcept
    {
        if (p != nullptr)
        {
            deletetree(p->leftchild);

            deletetree(p->rightchild);

            alloc.deallocate(p, 1); --cnt;
        }
    }

    template <typename T, typename Alloc>
    typename binarysearchtree<T, Alloc>::size_type
    binarysearchtree<T, Alloc>::level(pointer curr, const_pointer goal, size_type depth) const
    {
        if (curr == nullptr) return 0;

        if (curr->element == goal->element)
        {
            return depth;
        }

        size_t l = level(curr->leftchild, goal, depth + 1);

        if (l > 0) return l;

        size_t r = level(curr->rightchild, goal, depth + 1);

        if (r > 0) return r;

        return 0;
    }
}

#endif // BINARYSEARCHTREE_H
