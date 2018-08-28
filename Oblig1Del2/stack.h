#ifndef STACK_H
#define STACK_H

// This header contains the node which hold the data, and the stack which holds all the functionality and a pointer to the top node.
// A node holds a pointer to the next node.
// Templated to allow any type.

namespace ADS101
{
template <typename T>
struct node
{
    node(T d = 0, node* next = nullptr)
        : data{ d }, next{ next }
    {
    }

    T data;
    node* next;
};

template <typename T>
class stack
{
public:
    // Default constructor
    stack() : m_size{0}, m_first{nullptr}
    {
    }

    // The stl version does not have a clear function, so it's called in the destructor
    // to make sure that the code in main.cpp works with both std::stack and my version.
    ~stack()
    {
        clear();
    }

    // Adds a new node at the top
    void push(const T& data)
    {
        // Increments the size
        m_size++;
        // Temp pointer to the first node
        node<T>* temp = m_first;
        // The first node is now a new node with a pointer to the previous first node
        m_first = new node<T>(data, temp);
    }

    // Removes the node at the top
    void pop()
    {
        // Decrements the size
        m_size--;
        // Temp pointer to the first node
        node<T>* temp = m_first;
        // The first node is now the one after first
        m_first = m_first->next;
        // Delete the temp node
        delete temp;
    }

    // Returns the top nodes' data
    T& top() const
    {
        return m_first->data;
    }

    // Returns the size
    int size() const
    {
        return m_size;
    }

    // Bool to check if empty
    bool empty() const
    {
        return m_size == 0;
    }

private:
    int m_size;
    node<T>* m_first;

    // Called in the destructor
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
