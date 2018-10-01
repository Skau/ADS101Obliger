#ifndef QUEUE_H
#define QUEUE_H

namespace ADS101
{

template <typename T>
struct queueNode
{
    queueNode(T data) : mData{data}, next{nullptr}
    {
    }

    T mData;
    queueNode<T>* next;
};

template <typename T>
class queue
{
public:
    queue() : head{nullptr}, tail{nullptr}, mSize{0}
    {
    }

    ~queue()
    {
        clear();
    }

    void enqueue(T data)
    {
        if(!head)
        {
            head = new queueNode<T>(data);
            tail = head;
        }
        else
        {
            tail->next = new queueNode<T>(data);
            tail = tail->next;
        }
        mSize++;
    }

    void dequeue()
    {
        if(tail != nullptr)
        {
            auto temp = head;
            head = head->next;
            delete temp;
            mSize--;
        }
    }

    T front() { return head->mData; }

    T back() { return tail->mData; }

    int size() { return mSize; }

    bool empty() { return mSize == 0; }

private:
    queueNode<T>* head;
    queueNode<T>* tail;
    int mSize;

    void clear()
    {
        while(!empty())
        {
            dequeue();
        }
    }
};

}


#endif // QUEUE_H
