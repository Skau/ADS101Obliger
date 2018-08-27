#ifndef STACK_H
#define STACK_H

namespace ADS101
{
template <typename T>
struct node
{
    node(T data = 0, node* next = nullptr)
        : data{ data }, next{ next }
    {
    }

    T data;
    node* next;
};

template <typename T>
class stack
{
public:
    stack()
    {
        m_size = 0;
        m_first = new node<T>();
    }

    ~stack()
    {
        clear();
    }

    void push(T const data)
    {
        m_size++;
        node<T>* temp = m_first;
        m_first = new node<T>(data, temp);
    }

    void pop()
    {
        m_size--;
        node<T>* temp = m_first;
        m_first = m_first->next;
        delete temp;
    }

    T top() const
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
    node<T>* m_first;

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
