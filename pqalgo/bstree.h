#ifndef PQALGO_BSTREE_H
#define PQALGO_BSTREE_H

#include <iostream>

namespace pqalgo
{

template <typename K, typename V>
struct BSTreeNode
{
    BSTreeNode() : left(nullptr), right(nullptr) {}
    BSTreeNode(const K& _key, const V& _value)
        : left(nullptr), right(nullptr), key(_key), value(_value) {}
    BSTreeNode *left;
    BSTreeNode *right;
    K key;
    V value;
};

template <typename K, typename V>
class bstree
{
public:
    bstree() : root(nullptr) {}
    ~bstree();
    V& operator [] (const K& key);
    bool remove(const K& key);
    void preorder() const;
    void inorder() const;
    void postorder() const;
private:
    void destruct(BSTreeNode<K, V> *node);
    void __preorder(BSTreeNode<K, V> *node) const;
    void __inorder(BSTreeNode<K, V> *node) const;
    void __postorder(BSTreeNode<K, V> *node) const;
private:
    BSTreeNode<K, V> *root;
};

template <typename K, typename V>
bstree<K, V>::~bstree()
{
    destruct(root);
    root = nullptr;
}

template <typename K, typename V>
V& bstree<K, V>::operator [] (const K& key)
{
    if (root == nullptr) {
        root = new BSTreeNode<K, V>(key, V());
        return root->value;
    }

    auto p = root;
    auto q = p;
    while (p != nullptr) {
        if (key < p->key) {
            q = p;
            p = p->left;
        } else if (key > p->key) {
            q = p;
            p = p->right;
        } else {
            p->value = V();
            return p->value;
        }
    }

    if (key < q->key) {
        q->left = new BSTreeNode<K, V>(key, V());
        return q->left->value;
    } else {
        q->right = new BSTreeNode<K, V>(key, V());
        return q->right->value;
    }
}

template <typename K, typename V>
bool bstree<K, V>::remove(const K& key)
{
    auto p = root;
    auto q = p;
    while (p != nullptr && key != p->key) {
        q = p;
        if (key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (p == nullptr) {
        return false;
    }

    // 待删节点有两个叶子节点
    if (p->left != nullptr && p->right != nullptr) {
        auto pl = p->left;
        auto ql = p;
        // 在p的左子树找到最大叶子节点
        while (pl->right != nullptr) {
            ql = pl;
            pl = pl->right;
        }

        // 新建pnew准备取代p
        auto pnew = new BSTreeNode<K, V>(pl->key, pl->value);
        pnew->left = p->left;
        pnew->right = p->right;

        // p的父节点为nullptr，说明p为根节点
        if (q == nullptr) {
            root = q;
        }
        // p为其父节点的左叶子节点
        else if (p == q->left) {
            q->left = pnew;
        }
        // p为其父节点的右叶子节点
        else {
            q->right = pnew;
        }

        // 实际上是将两个叶子节点的情况转化为一个叶子节点的情况
        // 接下来准备处理ql及pl，对应有q及p

        // 如果p是最大左叶子节点的父节点，这意味着p的左子树只有一个叶子节点
        // 即将删除ql所指向的节点，q应转向新设置的pnew而不是ql
        if (p == ql) {
            q = pnew;
        } else {
            q = ql;
        }

        delete p;
        p = pl;
    }

    BSTreeNode<K, V> *pc;
    // 待删节点只有一个叶子节点，取得其叶子节点
    if (p->left != nullptr) {
        pc = p->left;
    } else {
        pc = p->right;
    }

    // 待删节点为根节点
    if (p == root) {
        root = pc;
    }
    // q指向p的叶子节点
    else {
        if (p == q->left) {
            q->left = pc;
        } else {
            q->right = pc;
        }
    }

    delete p;
    return true;
}

template <typename K, typename V>
void bstree<K, V>::preorder() const
{
    __preorder(root);
    std::cout << std::endl;
}

template <typename K, typename V>
void bstree<K, V>::inorder() const
{
    __inorder(root);
    std::cout << std::endl;
}

template <typename K, typename V>
void bstree<K, V>::postorder() const
{
    __postorder(root);
    std::cout << std::endl;
}

template <typename K, typename V>
void bstree<K, V>::destruct(BSTreeNode<K, V> *node)
{
    if (node == nullptr) {
        return;
    }
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template <typename K, typename V>
void bstree<K, V>::__preorder(BSTreeNode<K, V> *node) const
{
    if (node != nullptr) {
        std::cout << node->value << ' ';
        __preorder(node->left);
        __preorder(node->right);
    }
}

template <typename K, typename V>
void bstree<K, V>::__inorder(BSTreeNode<K, V> *node) const
{
    if (node != nullptr) {
        __inorder(node->left);
        std::cout << node->value << ' ';
        __inorder(node->right);
    }
}

template <typename K, typename V>
void bstree<K, V>::__postorder(BSTreeNode<K, V> *node) const
{
    if (node != nullptr) {
        __postorder(node->left);
        __postorder(node->right);
        std::cout << node->value << ' ';
    }
}

} // namespace pqalgo

#endif // PQALGO_BSTREE_H
