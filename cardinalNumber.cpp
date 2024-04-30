#include <iostream>
#include <cmath>

int main()
{
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;

    if (isCardinal(num))
    {
        std::cout << num << " is a cardinal number." << std::endl;
    }
    else
    {
        std::cout << num << " is not a cardinal number." << std::endl;
    }

    return 0;
}