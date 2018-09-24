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
            leftSub->parent = this;
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
            rightSub->parent = this;
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

void Node::remove(int data)
{
//    Node* nodeToRemove = find(data);
//    if(nodeToRemove)
//    {
//        std::cout << "Removing " << nodeToRemove->mData << std::endl;
//    }
//    else
//    {
//        std::cout << "Did not find node\n" << std::endl;
//        return;
//    }
    remove(*new Node(data), this);
}

Node *Node::find(int data)
{
    if(data == mData)
    {
        return this;
    }

    if(leftSub)
    {
       return leftSub->find(data);
    }

    if(rightSub)
    {
       return rightSub->find(data);
    }
    return nullptr;
}

void Node::remove(Node& comparable, Node* node)
{
    if(node == nullptr)
    {
        std::cout << "Return\n";
        return;
    }
    // if data is smaller - go to left subtree
    if(&comparable < node)
    {
        remove(comparable, node->leftSub);
    }
    // if data is greater - go to right subtree
    else if(&comparable > node)
    {
        remove(comparable, node->rightSub);
    }
    // if two children - find smallest in right subtree
    else if(node->leftSub && node->rightSub)
    {
        Node* minNode = findMin(node->rightSub);
        if(minNode)
        {
            std::cout << "minNode: " << minNode->mData << std::endl;;
            remove(*minNode, node->rightSub);
        }
        else
        {
            std::cout << "Return\n";
            return;
        }
    }
    else
    {
        auto oldNode = node;

        node = ( node->leftSub ) ? node->leftSub : node->rightSub;

        delete oldNode;
    }
}

Node* Node::findMin(Node *node)
{
    if(node == nullptr)
    {
        return nullptr;
    }

    if(node->leftSub == nullptr)
    {
        return node;
    }

    return findMin(node->leftSub);
}

Node* Node::findMax(Node *node)
{
    if(node == nullptr)
    {
        return nullptr;
    }

    if(node->rightSub == nullptr)
    {
        return node;
    }

    return findMax(node->rightSub);
}

void Node::replaceNode(int data, int replacementData)
{
    if(leftSub)
    {
        if(leftSub->data() == data)
        {
            auto replacementNode = new Node(replacementData);
            replacementNode->leftSub = leftSub->leftSub;
            replacementNode->rightSub = leftSub->rightSub;
            leftSub = nullptr;
            leftSub = replacementNode;
        }
        else
        {
            leftSub->replaceNode(data, replacementData);
        }
    }

    if(rightSub)
    {
        if(rightSub->data() == data)
        {
            auto replacementNode = new Node(replacementData);
            replacementNode->leftSub = rightSub->leftSub;
            replacementNode->rightSub = rightSub->rightSub;
            rightSub = nullptr;
            rightSub = replacementNode;
        }
        else
        {
            rightSub->replaceNode(data, replacementData);
        }
    }
}
