#include <iostream>

int main(void)
{
    int a = -5;
    int b = -2;
    int c = (a/b)*b + a%b == a;
    std::cout << c << std::endl;
    return 0;
}
