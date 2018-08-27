#ifndef OBJECT_H
#define OBJECT_H

#include <ostream>

class Object
{
public:
    Object(int data)
        :   m_data{ data }
    {
    }

    int getData() const { return m_data; }

    bool operator<(const Object& other)
    {
        return m_data < other.m_data;
    }

    bool operator>(const Object& other)
    {
        return m_data > other.m_data;
    }

    void operator=(int data)
    {
        m_data = data;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Object& obj)
    {
        stream << obj.m_data;
        return stream;
    }

private:
    int m_data;
};

#endif // OBJECT_H
