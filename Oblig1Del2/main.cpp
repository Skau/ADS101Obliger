#include <iostream>
#include "Stack.h"
#include <stack>

int main()
{
    ADS101::stack<float> stack;
    //std::stack<float> stack;

    stack.push(2.5);
    stack.push(3.5);
    stack.push(4.5);
    stack.push(5.5);

    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;

    if (!stack.empty())
    {
        std::cout << "The stack is not empty.\n";
    }
    else
    {
        std::cout << "The stack is empty.\n";
    }
    std::cout << "\n";

    std::cout << "pop()\n";
    stack.pop();
    std::cout << "\n";

    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;

    std::cin.get();
    return 0;
}


