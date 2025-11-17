#include <iostream>
#include <array>
#include <tuple>

std::tuple<int, int> analyze_mat(const std::array<std::array<int, 3>, 3> input) {
    int trace = input[0][0] + input[1][1] + input[2][2];
    int det0 = input[0][0] * (input[1][1]*input[2][2] - input[1][2]*input[2][1]);
    int det1 = input[0][1] * (input[1][0]*input[2][2] - input[2][0]*input[1][2]);
    int det2 = input[0][2] * (input[1][0]*input[2][1] - input[1][1]*input[2][0]);
    return std::make_tuple(trace, det0-det1+det2);
}

int main(void) {
    std::array<std::array<int, 3>, 3> input;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            std::cout << "Please input (" << i << "," << j << ")th element: " << std::endl;
            std::cin >> input[i][j];
        }
    }
    std::cout << "Analyzing the matrix: " << std::endl;
    std::cout << input[0][0] << ", " << input[0][1] << ", " << input[0][2] << std::endl;
    std::cout << input[1][0] << ", " << input[1][1] << ", " << input[1][2] << std::endl;
    std::cout << input[2][0] << ", " << input[2][1] << ", " << input[2][2] << std::endl;

    std::tuple<int, int> res = analyze_mat(input);
    std::cout << "Trace: " << std::get<0>(res) << ", Determinant: " << std::get<1>(res) << std::endl;
    return 0;
}