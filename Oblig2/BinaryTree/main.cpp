#include <iostream>
#include "binarytree.h"

int main()
{
    auto root = new ADS101::btree<int>(5);

    root->insert(7);
    root->insert(9);
    root->insert(0);
    root->insert(2);
    root->insert(3);
    root->insert(1);
    root->insert(8);
    root->insert(4);
    root->insert(6);

    std::cout << "Recursive inorder traversal:\n";
    root->printRecursiveInorder();
    std::cout << std::endl;

    std::cout << "Non recursive inorder traversal with stack:\n";
    root->printNonRecursiveInorder();
    std::cout << std::endl;

    std::cout << "Recursive preorder traversal:\n";
    root->printRecursivePreorder();
    std::cout << std::endl;

    std::cout << "Recursive postorder traversal:\n";
    root->printRecursivePostorder();
    std::cout << std::endl;

    std::cout << "Recursive breadth first level order traversal:\n";
    root->printRecursiveLevelOrder();
    std::cout << std::endl;

    std::cout << "Non recursive breadth first level order traversal with queue:\n";
    root->printNonRecursiveLevelOrder();
    std::cout << std::endl;

    std::cout << std::endl;
    root->remove(3);
    std::cout << std::endl;

    std::cout << "Recursive inorder traversal:\n";
    root->printRecursiveInorder();
    std::cout << std::endl;

    std::cout << "Non recursive inorder traversal with stack:\n";
    root->printNonRecursiveInorder();
    std::cout << std::endl;

    std::cout << "Recursive preorder traversal:\n";
    root->printRecursivePreorder();
    std::cout << std::endl;

    std::cout << "Recursive postorder traversal:\n";
    root->printRecursivePostorder();
    std::cout << std::endl;

    std::cout << "Recursive breadth first level order traversal:\n";
    root->printRecursiveLevelOrder();
    std::cout << std::endl;

    std::cout << "Non recursive breadth first level order traversal with queue:\n";
    root->printNonRecursiveLevelOrder();
    std::cout << std::endl;

    return 0;
}
