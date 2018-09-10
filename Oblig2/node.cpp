#include "node.h"
#include <iostream>

void Node::insert(int data)
{
    if(data < mData)
    {
        if(leftSub != nullptr)
        {
            leftSub->insert(data);
        }
        else
        {
            leftSub = new Node(data);
        }
    }
    else
    {
        if(rightSub != nullptr)
        {
            rightSub->insert(data);
        }
        else
        {
            rightSub = new Node(data);
        }
    }
}

void Node::intrav()
{
    if(leftSub)
    leftSub->intrav();

    std::cout << mData << " ";

    if(rightSub)
    rightSub->intrav();
}
