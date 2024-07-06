#include <stdio.h>

int main()
{
    // displaying capital and small letters
    char ch;
    printf("Enter any character: ");
    scanf("%c", &ch);

    if ((ch >= 'A' && ch <= 'Z'))
    {
        printf("%c is a Capital letter.", ch);
    }
    else if ((ch >= 'a' && ch <= 'z'))
    {
        printf("%c is a Smol letter.", ch);
    }
    else
    {
        printf("%c is not an alphabet.", ch);
    }

    return 0;
}