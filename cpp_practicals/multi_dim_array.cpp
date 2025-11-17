#include <iostream>

int** create_mat(int N) {
    int *a = new int[N*N];
    int **b = new int *[N];
    for (int i = 0; i < N; i++) {
        b[i] = a + (i*N);
    }
    return b;
}

void init_mat(int **mat, int N) {
    int val = 0;
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            mat[i][j] = val;
            val += 1;
        }
    }
}

void print_mat(int **mat, int N) {
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void square_mat_mul(int **A, int **B, int **C, int N) {
    // looping for C
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            int val = 0;
            for (int k=0; k<N; k++) {
                val += A[i][k] * B[k][j];
            }
            C[i][j] = val;
        }
    }
}

void free_mat(int **mat) {
    delete[] mat[0];
    delete[] mat;
}

int main(void) {
    int N;
    std::cout << "Enter dim: " << std::endl;
    std::cin >> N;

    int **mat_1 = create_mat(N);
    int **mat_2 = create_mat(N);
    int **mat_3 = create_mat(N);
    init_mat(mat_1, N);
    init_mat(mat_2, N);
    print_mat(mat_1, N);
    print_mat(mat_2, N);

    square_mat_mul(mat_1, mat_2, mat_3, N);
    print_mat(mat_3, N);

    free_mat(mat_1);
    free_mat(mat_2);
    free_mat(mat_3);
    return 0;
}