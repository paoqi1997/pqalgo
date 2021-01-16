#include <iostream>

#include "../forward_list.h"

using std::cout;
using std::endl;

int main()
{
    pqalgo::forward_list<int> li;

    li.insert(0, 1);
    li.insert(0, 2);
    li.insert(0, 3);

    auto p = li.begin();
    while (p != nullptr) {
        cout << p->element << ' ';
        p = p->next;
    }
    cout << endl;

    return 0;
}
