#include "historia.hpp"

#include <iostream>

int main()
{
    std::cout << "Running" << std::endl;
    Historia<int> history;
    history.previous();
    history.next();
}
