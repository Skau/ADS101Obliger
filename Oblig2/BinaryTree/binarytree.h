#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include "stack.h"
#include "queue.h"

namespace ADS101
{

template <typename T>
class btree
{
public:
    // Constructor takes a data of some type
    btree(T data) : mData{ data }, left{nullptr}, right{nullptr}
    {
    }

    // Inserts new node with given data
    void insert(T data)
    {
        if(data < mData)
        {
            if(left != nullptr)
            {
                left->insert(data);
            }
            else
            {
                left = new btree(data);
            }
        }
        else
        {
            if(right != nullptr)
            {
                right->insert(data);
            }
            else
            {
                right = new btree(data);
            }
        }
    }

    // Public function used to remove a node,
    // calls the private function
    void remove(T data)
    {
        if(exists(this, data))
        {
            std::cout << "Removing " << data << std::endl;
            remove(this, data);
        }
        else
        {
            std::cout << "Did not find data to remove\n";
        }
    }

    // Public function used to check if a given node exists,
    // calls the private function
    bool exists(T data)
    {
        return exists(this, data);
    }

    // Replaces a given node with a node with the data given
    void replaceNode(T data, T replacementData)
    {
        if(left)
        {
            if(left->data() == data)
            {
                auto replacementNode = new btree(replacementData);
                replacementNode->left = left->left;
                replacementNode->right = left->right;
                left = nullptr;
                left = replacementNode;
            }
            else
            {
                left->replaceNode(data, replacementData);
            }
        }

        if(right)
        {
            if(right->data() == data)
            {
                auto replacementNode = new btree(replacementData);
                replacementNode->left = right->left;
                replacementNode->right = right->right;
                right = nullptr;
                right = replacementNode;
            }
            else
            {
                right->replaceNode(data, replacementData);
            }
        }
    }

    // Prints tree using recursive preorder traversal
    void printRecursivePreorder()
    {
        std::cout << mData << " ";

        if(left)
            left->printRecursivePreorder();

        if(right)
            right->printRecursivePreorder();
    }

    // Prints tree using recursive inorder traversal
    void printRecursiveInorder()
    {
        if(left)
            left->printRecursiveInorder();

        std::cout << mData << " ";

        if(right)
            right->printRecursiveInorder();
    }

    // Prints inorder traversal using a stack
    void printNonRecursiveInorder()
    {
        ADS101::stack<btree*> stack;
        auto currentNode  = this;

        while(currentNode || !stack.empty())
        {
            while(currentNode)
            {
                stack.push(currentNode);
                currentNode = currentNode->left;
            }

            currentNode = stack.top();
            stack.pop();

            std::cout << currentNode->mData << " ";

            currentNode =  currentNode->right;
        }

    }

    // Prints tree using recursive postorder traversal
    void printRecursivePostorder()
    {
        if(left)
            left->printRecursivePostorder();

        if(right)
            right->printRecursivePostorder();

        std::cout << mData << " ";
    }

    // Prints tree using a recursive breadth-first level order traversal
    void printRecursiveLevelOrder()
    {
        int h = height();
        for(int i = 1; i <= h; i++)
        {
            std::cout << "Depth " << i << ": ";
            printLevel(i);
            if(i != h)
            std::cout << std::endl;
        }
    }

    // Prints the tree using a non recursive breadth first traversal using queue
    void printNonRecursiveLevelOrder()
    {
        auto queue = new ADS101::queue<btree*>();
        queue->enqueue(this);

        while(!queue->empty())
        {
            auto node = queue->front();
            std::cout << node->mData << " ";
            queue->dequeue();
            if(node->left)
            {
                queue->enqueue(node->left);
            }
            if(node->right)
            {
                queue->enqueue(node->right);
            }
        }
    }

    int data() { return mData; }

private:
    // Returns if the given data is found
    bool exists(btree* node, T data)
    {
        do
        {
            if(data > node->mData)
            {
                node = node->right;
            }
            else if(data < node->mData)
            {
                node = node->left;
            }
            else
            {
                return true;
            }
        } while(node != nullptr);

        return false;
    }

    // Removes a node with the given data, node is the root node
    btree* remove(btree* node, T data)
    {
        if(node == nullptr)
        {
            return node;
        }

        // Go left
        if(data < node->mData)
        {
            node->left = remove(node->left, data);
        }
        // Go right
        else if(data > node->mData)
        {
            node->right = remove(node->right, data);
        }
        // At correct node
        else
        {
            // If two nodes
            if(node->left && node->right)
            {
                auto temp = findMin(node->right);
                if(temp)
                {
                    node->mData = temp->mData;
                    node->right = remove(node->right, node->mData);
                }
            }
            // If no nodes
            else if(!node->left && !node->right)
            {
                node = nullptr;
            }
            // If right node
            else if(node->right)
            {
                auto temp = node->right;
                node = nullptr;
                return temp;
            }
            // If left node
            else if(node->left)
            {
                auto temp = node->left;
                node = nullptr;
                return temp;
            }
        }
        return node;
    }

    // Returns the lowest node from the given root node
    btree* findMin(btree* node)
    {
        auto currentNode = node;

        while(currentNode->left != nullptr)
        {
            currentNode = currentNode->left;
        }

        return currentNode;
    }

    // Returns the highest node from the given root node
    btree* findMax(btree* node)
    {
        auto currentNode = node;

        while(currentNode != nullptr)
        {
            currentNode = currentNode->right;
        }

        return currentNode;
    }

    // Returns the height of the tree
    int height()
    {
        int leftHeight = left ? left->height() : 0;
        int rightHeight = right ? right->height() : 0;

        // To make sure that we get the max height
        return std::max(leftHeight, rightHeight) + 1;
    }

    // Recursive function to print data on the level given
    void printLevel(int level)
    {
        if(level == 1)
        {
            std::cout << mData << " ";
        }
        else if(level > 1)
        {
            if(left)
            {
                left->printLevel(level - 1);
            }
            if(right)
            {
                right->printLevel(level - 1);
            }
        }
    }

    T mData;
    btree* left;
    btree* right;
};

}

#endif // BINARYTREE_H
