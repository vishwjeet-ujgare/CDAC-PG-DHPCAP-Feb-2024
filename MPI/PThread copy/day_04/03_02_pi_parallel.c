#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define N 999999999  // Number of iterations

int num_threads; // Number of threads (set dynamically)

struct timeval stop_time, start_time;
double exe_time;

void *monte_carlo_pi(void *arg) {
    long tid = (long) arg;
    double dx = 1.0 / N;
    double area = 0.0;
    srand(tid); // Seed random number generator with thread ID

    for (long i = tid; i < N; i += num_threads) {
        double x = i * dx;
        double y = sqrt(1 - x * x);
        area += y * dx;
    }

    return (void *)area; // Return partial area directly
}

int main() {
    pthread_t *threads;
    double *partial_areas;
    double pi, total_area = 0.0;

    // Get the number of available cores
    num_threads = sysconf(_SC_NPROCESSORS_CONF);
    printf("Using %d threads\n", num_threads);

    // Allocate memory for threads and partial areas
    threads = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
    partial_areas = (double *)malloc(sizeof(double) * num_threads);
    if (threads == NULL || partial_areas == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    gettimeofday(&start_time, NULL);

    // Create threads and calculate partial areas
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, monte_carlo_pi, (void *)i);
    }

    // Wait for all threads to finish and collect partial areas
    for (long i = 0; i < num_threads; i++) {
        double area;
        pthread_join(threads[i], (void **)&area); // Get return value
        total_area += area;
    }

    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

    pi = 4.0 * total_area;
    printf("\n Value of pi is = %.16lf\n Execution time is = %lf seconds\n", pi, exe_time);

    // Free allocated memory
    free(threads);
    free(partial_areas);

    return 0;
}
