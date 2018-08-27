#ifndef STACK_H
#define STACK_H


// This header contains the node which hold the data, and the stack which holds all the functions and a pointer to the the top node
// All nodes hold the pointer to the next node.
// They are both templated to allow any type (well most anyway - std::string does not work out of the box, but const char* does)
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

    // The clear function is called in the destructor, so main works with both std::stack and my version
    ~stack()
    {
        clear();
    }

    // Adds a new node the the top
    void push(T const data)
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
    T top() const
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

    // Declared here and called in the destructor
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
