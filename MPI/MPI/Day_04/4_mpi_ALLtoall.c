#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *recv_data = (int *)malloc(size * sizeof(int));
    int *send_data = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        send_data[i] = rank + i * 10;
    }

    MPI_Alltoall(send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received data : ", rank);
   
    for (int i = 0; i < size; i++)
    {
        printf("%d ",recv_data[i]);
    }

    printf("\n");
    free(recv_data);
    free(send_data);

    MPI_Finalize();
    return 0;
}
