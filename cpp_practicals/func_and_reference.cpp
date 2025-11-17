#include <iostream>
#include <cmath>

int sum(int a, int b) {
    return a+b;
}

void decrease(int &a, int b) {
    a = a-b;
}

int q(double a, double b, double c, double &x1, double &x2) {
    double delta = b*b - (4*a*c);
    if (delta <= 0) {
        return 0;
    } else {
        double sqrt_delta = sqrt(delta);
        x1 = (-b+sqrt_delta)/(2*a);
        x2 = (-b-sqrt_delta)/(2*a);
        return (delta==0) ? 1 : 2;
    }
}

int main(void) {
    int a = 10;
    int b = 3;
    double c, d;
    a = sum(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    decrease(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    int num = q(2, 3, 4, c, d);
    std::cout << "nums: " << num << ", x1: " << c << ", x2: " << d << std::endl;
    
    return 0;
}