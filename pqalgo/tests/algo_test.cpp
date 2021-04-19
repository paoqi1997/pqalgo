#include <iostream>
#include <string>

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

    pqalgo::Trie<26> trie;
    trie.insert("my");
    trie.insert("mydb");
    trie.insert("mysql");

    cout << trie.find("milk") << endl;
    cout << trie.find("mysql") << endl;

    return 0;
}
