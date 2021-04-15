#ifndef PQALGO_TRIE_H
#define PQALGO_TRIE_H

#include <cstring>

namespace pqalgo
{

template <std::size_t N>
struct TrieNode
{
    TrieNode() : cnt(0), isEnd(false) {
        for (std::size_t i = 0; i < N; ++i) {
            children[i] = nullptr;
        }
    }
    TrieNode *children[N];
    int cnt;
    bool isEnd;
};

template <std::size_t N>
class Trie
{
public:
    Trie() : root(new TrieNode<N>()) {}
    ~Trie() {
        destruct(root);

        delete root;
        root = nullptr;
    }
    void insert(const char *s) {
        auto p = root;

        for (std::size_t i = 0; i < std::strlen(s); ++i) {
            char c = s[i];

            if (p->children[c - 'a'] == nullptr) {
                p->children[c - 'a'] = new TrieNode<N>();
                ++p->cnt;
            }

            p = p->children[c - 'a'];
        }

        p->isEnd = true;
    }
    bool find(const char *s) {
        auto p = root;

        for (std::size_t i = 0; i < std::strlen(s); ++i) {
            char c = s[i];

            if (p->children[c - 'a'] == nullptr) {
                return false;
            }

            p = p->children[c - 'a'];
        }

        return p->isEnd;
    }
private:
    void destruct(TrieNode<N> *node) {
        for (std::size_t i = 0; i < N; ++i) {
            if (node->children[i] == nullptr) {
                continue;
            }

            destruct(node->children[i]);

            delete node->children[i];
            node->children[i] = nullptr;

            if (--node->cnt == 0) {
                break;
            }
        }
    }
private:
    TrieNode<N> *root;
};

} // namespace pqalgo

#endif // PQALGO_TRIE_H
