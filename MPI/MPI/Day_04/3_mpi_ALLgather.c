#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process sends its rank
    int send_data = rank; 
    int *recv_data = NULL;

    // Allocate memory for receiving data
    // Allocate memory for receiving data
    recv_data = (int *)malloc(size * sizeof(int)); 

    // Gather the data from all processes to the root process
    MPI_Gather(&send_data, 1, MPI_INT, recv_data,1, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast the data from the root process to all processes
    MPI_Bcast(recv_data, size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++)
    {
        printf("Data at %d index = %d and prineted by %d \n",i, recv_data[i], rank);
    }

    printf("\n");
    free(recv_data);
 
    MPI_Finalize();
    return 0;
}
