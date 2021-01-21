#ifndef PQALGO_BSTREE_H
#define PQALGO_BSTREE_H

namespace pqalgo
{

template <typename K, typename V>
struct BSTreeNode
{
    BSTreeNode() : left(nullptr), right(nullptr) {}
    BSTreeNode(K _key, V _value) : left(nullptr), right(nullptr), key(_key), value(_value) {}
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
private:
    void destruct(BSTreeNode<K, V> *node);
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
void bstree<K, V>::destruct(BSTreeNode<K, V> *node)
{
    if (node == nullptr) {
        return;
    }
    destruct(node->left);
    destruct(node->right);
    delete node;
}

} // namespace pqalgo

#endif // PQALGO_BSTREE_H
