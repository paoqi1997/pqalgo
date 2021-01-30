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
     * 1 + + + 5
     *       +   +
     *     3 + + + 7
     */
    bst[2] = 2;
    bst[1] = 1;
    bst[5] = 5;
    bst[3] = 3;
    bst[7] = 7;

    bst.preorder();
    bst.inorder();
    bst.postorder();

    bst.remove(5);

    bst.preorder();
    bst.inorder();
    bst.postorder();

    cout << "ok." << endl;

    return 0;
}
