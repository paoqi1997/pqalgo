#include <iostream>
#include <string>

#include <pqalgo/lru.h>
#include <pqalgo/kmp.h>
#include <pqalgo/trie.h>

using std::cout;
using std::endl;

int main()
{
    cout << "[pqalgo/kmp]" << endl;

    std::string s = "12 345 6789 0", p = "789";

    int idx1 = pqalgo::bf(s.c_str(), p.c_str());
    int idx2 = pqalgo::kmp(s.c_str(), p.c_str());

    if (idx1 != -1) {
        cout << idx1 << ' ' << s.substr(idx1, p.length()) << endl;
    }
    if (idx2 != -1) {
        cout << idx2 << ' ' << s.substr(idx2, p.length()) << endl;
    }

    cout << "[pqalgo/trie]" << endl;

    pqalgo::Trie trie;

    trie.insert("my");
    trie.insert("mydb");
    trie.insert("mysql");

    cout << trie.find("milk") << ' ' << trie.find("mysql") << endl;

    cout << trie.startsWith("mike") << ' ' << trie.startsWith("my") << endl;

    cout << "[pqalgo/lru]" << endl;

    pqalgo::LRU<int, int> lru(5);

    lru[1] = 1;
    lru[3] = 3;
    lru[5] = 5;
    lru[7] = 7;
    lru[9] = 9;

    for (auto it = lru.begin(); it != lru.end(); ++it) {
        cout << it->first << ':' << it->second << ' ';
    }
    cout << endl;

    lru[6] = 6;
    cout << lru[4] << endl;

    for (auto& kv : lru) {
        cout << kv.first << ':' << kv.second << ' ';
    }
    cout << endl;

    return 0;
}
