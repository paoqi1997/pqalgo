#include <iostream>
#include <string>

#include <pqalgo/kmp.h>

using std::cout;
using std::endl;

int main()
{
    std::string s = "12 345 6789 0", p = "789";

    std::size_t idx = pqalgo::kmp(s.c_str(), p.c_str());

    cout << idx << ' ' << s.substr(idx, p.length()) << endl;

    return 0;
}
