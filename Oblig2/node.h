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

    Node* find(int data);

    void replaceNode(int dataToReplace, int replacementData);

    int data() { return mData; }

private:
    void remove(Node& Comparable, Node* node);

    Node* findMin(Node* node);
    Node* findMax(Node* node);

    bool operator==(const Node& node)
    {
        return mData == node.mData;
    }

    bool operator<(const Node& node)
    {
        return mData < node.mData;
    }

    bool operator>(const Node& node)
    {
        return mData < node.mData;
    }

    int mData;
    Node* leftSub;
    Node* rightSub;
    Node* parent;
};

#endif // NODE_H
