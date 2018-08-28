#ifndef OBJECT_H
#define OBJECT_H

#include <ostream>

class Object
{
public:
    // Constructor
    Object(int data) :  m_data{ data }
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
    void operator=(int data)
    {
        m_data = data;
    }

    int operator()()
    {
        return m_data;
    }



private:
    int m_data;
};

#endif // OBJECT_H
