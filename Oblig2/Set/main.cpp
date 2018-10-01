// Write an implementation of the set class, with associated iterators using a binary
// search tree. Add to each node a link to the next smallest and next largest node.
// To make your code simpler, add a header and tail node which are not part of the
// binary search tree, but help make the linked list part of the code simpler.

#include <iostream>
#include "binarytree.h"
#include "treeiterator.h"

using namespace ADS101;

int main()
{
    auto root = new treeNode<int>(25);

    root->insert(65);
    root->insert(32);
    root->insert(15);
    root->insert(19);
    root->insert(95);
    root->insert(40);



    return 0;
}
