#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

int number ; 
MPI_Status status;

if (rank  == 0 )
{
    number = 100;
    MPI_Send( &number  , 1 , MPI_INT ,1 , 0, MPI_COMM_WORLD);MPI_Send( &number  , 1 , MPI_INT ,1 , 0, MPI_COMM_WORLD);
}
else if (rank  == 1){
    MPI_Recv( &number , 1,MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status);
    printf("Process 1 reveived number %d from process %d with tag %d\n",number  ,status.MPI_SOURCE, status.MPI_TAG);
}


    MPI_Finalize();
    return 0;
}
