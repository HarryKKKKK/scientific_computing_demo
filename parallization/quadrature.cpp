#include <iostream>
#include <iomanip>
#include <math.h>
#include <mpi.h>

#define STEPS 27720000

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int start = (STEPS / size) * rank;
    int end = (STEPS / size) * (rank + 1);

    double total = 0.0;

    for (int i = start; i < end; i++) {
        total += exp( -pow(10.0 * ((i + 0.5) / (STEPS + 1)), 2));
    }

    std::cout << std::fixed << std::setprecision(16);
    std::cout << "thread " << rank << ": calculating [" << start << ", " << end << ") - " << total << std::endl;

    double global_total = 0.0;
    double* all_totals ;
    if (rank == 0) {
        all_totals = (double*) malloc(size * sizeof(double)); 
    }

    // MPI_Allreduce(&total, &global_total, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    // MPI_Reduce(&total, &global_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Gather(&total, 1, MPI_DOUBLE, all_totals, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i ++) {
            global_total += all_totals[i];
        }
        free(all_totals);
    }

    if (rank == 0) {
        std::cout << "The result is: " << 10.0 * global_total / STEPS << std::endl;
        std::cout << "The \'true\' value is: " << 0.5*std::sqrt(3.1415926) << std::endl;
    }

    MPI_Finalize();
    return 0;
}
