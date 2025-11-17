#include <iostream>
#include <cmath>
#include <format>
#include <string>
using namespace std;
// g++ .\solve_quadratic.cpp -std=c++20


// Calculation
void calculate_root(float a, float b, float c) {
    float delta = (b*b) - (4*a*c);
    if (delta >= 0) {
        float sqrt_delta = sqrt(delta);
        float x1 = (-b + sqrt_delta) / (2*a);
        float x2 = (-b - sqrt_delta) / (2*a);
        std::cout << "The solutions are " << x1 << " and " << x2 << std::endl;
        
    } else {
        float sqrt_delta = sqrt(-delta);
        float real = (-b) / (2*a);
        float cplx = (sqrt_delta) / (2*a);
        string res = format("The solutions are {}+{}i, {}-{}i", real, cplx, real, cplx);
        std::cout << res << std::endl;
    }
}

int main(void)
{
    // Read in values
    float a, b, c;
    std::cout << "Solving a*x*x+b*x+c=0:" << std::endl;
    std::cout << "Enter a: " << std::endl;
    std::cin >> a;
    std::cout << "Enter b: " << std::endl;
    std::cin >> b;
    std::cout << "Enter c: " << std::endl;
    std::cin >> c;

    calculate_root(a, b, c);
    
    return 0;
}
