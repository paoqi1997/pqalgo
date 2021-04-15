#include <iostream>
#include <string>

#include <pqalgo/kmp.h>

using std::cout;
using std::endl;

int main()
{
    std::string s = "12 345 6789 0", p = "789";

    std::size_t idx1 = pqalgo::bf(s.c_str(), p.c_str());
    std::size_t idx2 = pqalgo::kmp(s.c_str(), p.c_str());

    cout << idx1 << ' ' << s.substr(idx1, p.length()) << endl;
    cout << idx2 << ' ' << s.substr(idx2, p.length()) << endl;

    return 0;
}
