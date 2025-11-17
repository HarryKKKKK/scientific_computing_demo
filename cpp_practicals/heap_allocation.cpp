#include <iostream>

void calcNextRow(const int* prevRow, int* nextRow, int rowNo) {
    nextRow[0] = 1;
    for (int i = 0; i < rowNo-1; i++) {
        nextRow[i+1] = prevRow[i] + prevRow[i+1];
    }
    nextRow[rowNo] = 1;
}

void print_row(const int *row, int rowNo) {
    for (int i = 0; i < rowNo+1; i++) {
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    int n;
    std::cout << "Enter an integer: " << std::endl;
    std::cin >> n;

    int *prevRow = new int[n+1];
    int *nextRow = new int[n+1];
    prevRow[0] = 1;

    print_row(prevRow, 0);
    for (int j = 0; j < n; j++) {
        std::cout << "loop " << j << ": ";
        
        calcNextRow(prevRow, nextRow, j);
        print_row(nextRow, j);

        // std::swap(nextRow, prevRow);
        int* tmpRow = prevRow;
        prevRow = nextRow;
        nextRow = tmpRow;
    }
    
    delete[] nextRow;
    delete[] prevRow;
    return 0;
}