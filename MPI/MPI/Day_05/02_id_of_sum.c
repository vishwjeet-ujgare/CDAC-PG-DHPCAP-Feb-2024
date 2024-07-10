#include <mpi.h>
#include <stdio.h>


// int MPI_Reduce (
//         void * sendbuf , /* pointer to send buffer */
//         void * recvbuf , /* pointer to receive buffer */
//         int count , /* number of items to send */
//         MPI_Datatype datatype , /* datatype of buffer elements */
//         MPI_Op op , /* reduce operation */
//         int root , /* rank of root process */
//         MPI_Comm comm ) /* MPI communicator to use */


int main(int argc, char** argv) {
  const int MASTER_RANK = 0;
    MPI_Init(&argc, &argv);

    int size,rank;
    int sum = 0;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  
    MPI_Reduce(&rank, &sum, 1, MPI_INT, MPI_SUM, MASTER_RANK, MPI_COMM_WORLD);


    if (rank == MASTER_RANK) {
        printf("Sum of ranks: %d\n", sum);
    }


    MPI_Finalize();
    return 0;
}