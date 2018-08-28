#include <iostream>
#include "Stack.h"
#include <stack>

int main()
{
    // Both my version and the stl one work the exact same way with the functions below
    ADS101::stack<std::string> stack;
    //std::stack<std::string> stack;

    stack.push("string");
    stack.push("string1");
    stack.push("string2");
    stack.push("string3");

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

    std::cout << "stack.pop();\n";
    stack.pop();
    std::cout << "\n";

    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;
    std::cout << "\n";

    return 0;
}


