#include <iostream>
#include "Stack.h"
#include <stack>

int main()
{
    // Both my version and the stl one work the exact same way with the functions below
    ADS101::stack<std::string> stack;
    //std::stack<std::string> stack;

    stack.push("2.5");
    stack.push("3.5");
    stack.push("4.5");
    stack.push("5.5");

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
    std::cout << "\n";

    ADS101::stack<std::string> stack2 = stack;
    //std::stack<std::string> stack2 = stack;

    std::cout << "stack2: Top: " << stack.top() << std::endl;
    std::cout << "stack2: Size: " << stack.size() << std::endl;

    std::cin.get();
    return 0;
}


