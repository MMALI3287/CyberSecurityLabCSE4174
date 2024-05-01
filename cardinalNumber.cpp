#include <iostream>
#include <cmath>

bool isCardinal(double num)
{
    double intPart;
    double fracPart = modf(num, &intPart);
    return fracPart == 0 && num >= 0;
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