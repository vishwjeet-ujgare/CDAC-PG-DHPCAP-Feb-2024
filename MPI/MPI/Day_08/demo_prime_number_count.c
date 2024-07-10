#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

#define N 1000000

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int local_count = 0, global_count = 0;
    double exe_time;
    struct timeval start_time, stop_time;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes

    // Start timer
    gettimeofday(&start_time, NULL);

    // Calculate the range of numbers for each process
    int chunk_size = (N - 2) / size; // Number of elements each process handles
    int start = rank * chunk_size + 2; // Start of range for this process
    int end = (rank == size - 1) ? N : start + chunk_size; // End of range

    // Count primes in the assigned range
    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            local_count++;
        }
    }

    // Collect the local counts from all processes and sum them up
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Stop timer
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

    // Print the result from the root process (rank 0)
    if (rank == 0) {
        printf("\nNumber of prime numbers = %d\nExecution time is = %lf seconds\n", global_count, exe_time);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
