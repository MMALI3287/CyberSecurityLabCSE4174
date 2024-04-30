#include <iostream>

bool isCardinal(double num)
{
    // Check if the number is non-negative and has no fractional part
    return num >= 0 && num == static_cast<double>(num);
}

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