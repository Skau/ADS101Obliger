#include <iostream>
#include "node.h"

int main()
{
    auto root = new ADS101::Node<int>(5);

    root->insert(7);
    root->insert(9);
    root->insert(0);
    root->insert(2);
    root->insert(3);
    root->insert(1);
    root->insert(8);
    root->insert(4);
    root->insert(6);

    std::cout << "Recursive preorder traversal:\n";
    root->printRecursivePreorderTraversal();
    std::cout << std::endl;

    std::cout << "Recursive inorder traversal:\n";
    root->printRecursiveInorderTraversal();
    std::cout << std::endl;

    std::cout << "Recursive postorder traversal:\n";
    root->printRecursivePostorderTraversal();
    std::cout << std::endl;

    std::cout << "Breadth first level order traversal:\n";
    root->printLevelOrderTraversal();
    std::cout << std::endl;

    root->remove(3);

//    std::cout << "Recursive preorder traversal:\n";
//    root->printRecursivePreorderTraversal();
//    std::cout << std::endl;

//    std::cout << "Delete 3\n";
//    root->remove(3);

//    std::cout << "Recursive preorder traversal:\n";
//    root->printRecursivePreorderTraversal();
//    std::cout << std::endl;

//    std::cout << "Delete 4\n";
//    root->remove(4);

    std::cout << "Recursive preorder traversal:\n";
    root->printRecursivePreorderTraversal();
    std::cout << std::endl;

    std::cout << "Recursive inorder traversal:\n";
    root->printRecursiveInorderTraversal();
    std::cout << std::endl;

    std::cout << "Recursive postorder traversal:\n";
    root->printRecursivePostorderTraversal();
    std::cout << std::endl;

    std::cout << "Breadth first level order traversal:\n";
    root->printLevelOrderTraversal();
    std::cout << std::endl;

    return 0;
}
