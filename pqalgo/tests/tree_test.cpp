#include <iostream>

#include "../bstree.h"

using std::cout;
using std::endl;

int main()
{
    cout << "[pqalgo/bstree]" << endl;
    pqalgo::bstree<int, int> bst;

    /**
     *     2
     *   +   +
     * 1 + + + 3
     */
    bst[2] = 2;
    bst[1] = 1;
    bst[3] = 3;

    bst.preorder();
    bst.inorder();
    bst.postorder();

    cout << "ok." << endl;

    return 0;
}
