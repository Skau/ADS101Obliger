#ifndef OBJECT_H
#define OBJECT_H

#include <ostream>

template <typename T>
class Object
{
public:
    // Constructor
    Object(T d) :  m_data{ d }
    {
    }

    //***** Overloads *****//

    bool operator<(const Object& other)
    {
        return m_data < other.m_data;
    }

    bool operator>(const Object& other)
    {
        return m_data > other.m_data;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Object& obj)
    {
        stream << obj.m_data;
        return stream;
    }

    // These last two are here so that it's easier to use during sorting
    void operator=(T data)
    {
        m_data = data;
    }

    T operator()()
    {
        return m_data;
    }

private:
    T m_data;
};

#endif // OBJECT_H
