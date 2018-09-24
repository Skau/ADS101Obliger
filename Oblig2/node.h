#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node(int data) : mData{ data }, leftSub{nullptr}, rightSub{nullptr}
    {
    }

    void insert(int data);

    void intrav();

    void remove(int data);

    void replaceNode(int dataToReplace, int replacementData);

    int data() { return mData; }

private:
    void removeNode(int data, Node* node);

    Node* findMin(Node* node);
    Node* findMax(Node* node);

    int mData;
    Node* leftSub;
    Node* rightSub;
    Node* parent;
};

#endif // NODE_H
