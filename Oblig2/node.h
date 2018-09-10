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

    int data() { return mData; }

private:
    int mData;
    Node* leftSub;
    Node* rightSub;
};

#endif // NODE_H
