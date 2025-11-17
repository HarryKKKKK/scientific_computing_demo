#include <iostream>
// #include <format>
#include <string>
#include <fstream>

int read_n() {
    int n;
    std::cout << "Please enter the maximum square: " << std::endl;
    std::cin >> n;

    while (n < 0) {
        std::cout << "Please re-enter a valid n: " << std::endl;
        std::cin >> n;
    }
    return n;
}

void print_vals(int n) {
    std::ofstream MyFile("squares.txt");

    for (int i = 0; i <= n; i++) {
        // std::string res = std::format("{} * {} = {}", i, i, i*i); 
        std::string res = std::to_string(i) + " * " + std::to_string(i) + " = " + std::to_string(i*i);
        std::cout << res << std::endl;

        MyFile << std::to_string(i) + "\t" + std::to_string(i*i) + "\n";
    }

    MyFile.close();
}

int main(void) {
    int n = read_n();
    print_vals(n);

    return 0;
}