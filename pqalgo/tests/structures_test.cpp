#include <iostream>

#include <pqalgo/forward_list.h>
#include <pqalgo/list.h>

using std::cout;
using std::endl;

int main()
{
    cout << "[pqalgo/forward_list]" << endl;
    pqalgo::forward_list<int> fli;

    fli.insert(0, 1);
    fli.insert(1, 2);
    fli.insert(2, 3);

    auto fp = fli.begin();
    while (fp != nullptr) {
        cout << fp->element << ' ';
        fp = fp->next;
    }
    cout << endl;

    cout << "[pqalgo/list]" << endl;
    pqalgo::list<int> li;

    li.insert(0, 1);
    li.insert(1, 2);
    li.insert(2, 4);

    auto p = li.begin();
    while (p != li.end()) {
        cout << p->element << ' ';
        p = p->next;
    }
    cout << endl;

    return 0;
}
