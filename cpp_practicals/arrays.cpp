#include <iostream>
#include <array>


void partial_sum(std::array<int, 20> a, std::array<int, 20> &b) {
    int temp_sum = 0;
    for (int i = 0; i<20; i++) {
        temp_sum += a[i];
        b[i] = temp_sum;
    }
}

void print_arr(std::array<int, 20> array) {
    // A fancy but useless way.
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << std::endl;
    }
}

int main(void) {
    std::array<int, 20> a, b;
    for (int i = 0; i < 20; i++) {
        a[i] = i;
    }
    partial_sum(a, b);
    print_arr(b);
    
    return 0;
} 