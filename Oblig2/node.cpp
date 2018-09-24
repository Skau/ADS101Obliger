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
    std::cout << "Removing " << data << std::endl;
    removeNode(data, this);
}

void Node::removeNode(int data, Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    // if data is smaller - go to left subtree
    if(data < node->data())
    {
        removeNode(data, node->leftSub);
    }
    // if data is greater - go to right subtree
    else if(data > node->data())
    {
        removeNode(data, node->rightSub);
    }
    // if two children - find smallest in right subtree
    else if(node->leftSub && node->rightSub)
    {
        int minData = findMin(node->rightSub)->data();
        removeNode(minData, node->rightSub);

    }
    else
    {



//        node->parent->leftSub = ( node->leftSub ) ? node->leftSub : node->rightSub;
//        node->parent->leftSub = node->rightSub;

        if(node->leftSub)
        {
            leftSub = node->leftSub;
        }

        if(node->rightSub)
        {
            rightSub = node->rightSub;
        }

        node = nullptr;

//        delete tempNode;
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
