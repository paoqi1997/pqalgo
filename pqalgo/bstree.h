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
