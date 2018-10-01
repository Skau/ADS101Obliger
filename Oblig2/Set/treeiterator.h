#ifndef TREEITERATOR_H
#define TREEITERATOR_H
#include "binarytree.h"

namespace ADS101
{

template <typename T>
class TreeIterator
{
  friend class treeNode;

public:
  TreeIterator(treeNode<T> node) : currentNode{node}
  {
  }

  ~TreeIterator() = default;

  T& operator*()
  {
      return currentNode->data();
  }

  T& operator->()
  {
    return &(currentNode->data());
  }

  TreeIterator<T>& operator=(const TreeIterator& other)
  {
      this->currentNode = other.currentNode;
      return *this;
  }
  TreeIterator& operator++(const TreeIterator& other);

  bool operator==(const TreeIterator& other) const
  {
      return currentNode == other.currentNode;
  }

  bool operator!=(const TreeIterator& other) const
  {
      return currentNode != other.currentNode;
  }

  ADS101::treeNode<T>* node()
  {
    return currentNode;
  }

  static TreeIterator begin(treeNode* rootNode)
  {
      if(rootNode == nullptr)
      {
          return TreeIterator(rootNode);
      }

      while(true)
      {
          if(rootNode->left)
          {
              rootNode = rootNode->left;
          }
          else if(rootNode->right)
          {
              rootNode = rootNode->right;
          }
          else
          {
              return TreeIterator(rootNode);
          }
      }
  }

private:
  ADS101::treeNode<T>* currentNode;
};



#endif // TREEITERATOR_H
