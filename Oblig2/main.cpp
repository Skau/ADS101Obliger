#include <iostream>
#include "node.h"

int main()
{
    Node* rot = new Node(5);

    rot->insert(7);
    rot->insert(9);
    rot->insert(0);
    rot->insert(2);
    rot->insert(3);
    rot->insert(1);
    rot->insert(8);
    rot->insert(4);
    rot->insert(6);

    rot->intrav();
    std::cout << std::endl;

    return 0;
}
