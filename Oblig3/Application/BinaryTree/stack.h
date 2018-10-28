#ifndef STACK_H
#define STACK_H

namespace ADS101
{
template <typename T>
struct stackNode
{
    stackNode(T d = 0, stackNode* next = nullptr)
        : data{ d }, next{ next }
    {
    }

    T data;
    stackNode* next;
};

template <typename T>
class stack
{
public:
    stack() : m_size{0}, m_first{nullptr}
    {
    }

    ~stack()
    {
        clear();
    }

    void push(const T& data)
    {
        m_size++;
        stackNode<T>* temp = m_first;
        m_first = new stackNode<T>(data, temp);
    }

    void pop()
    {
        m_size--;
        stackNode<T>* temp = m_first;
        m_first = m_first->next;
        delete temp;
    }

    T& top() const
    {
        return m_first->data;
    }

    int size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0;
    }

private:
    int m_size;
    stackNode<T>* m_first;

    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }
};
}

#endif // STACK_H
