#ifndef STACK_H
#define STACK_H

template <typename T>
class stack
{
public:
    stack(int size)
        : m_size{ size }
    {
        init();
    }

    ~stack()
    {
        clear();
    }

    void init()
    {
        T* data = new T[m_size];
        for(int i = 0; i < m_size; i++)
        {
            data[i] = 0;
        }
    }

    operator[](int i)
    {
        return data[i];
    }


private:
    int m_size;
    T* data;

    void clear()
    {

    }
};

#endif // STACK_H
