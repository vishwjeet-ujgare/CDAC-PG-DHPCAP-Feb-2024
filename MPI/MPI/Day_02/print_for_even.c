#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv); //mpi related environment initialize , after this mpi code is written and function call, 
    //resources allocated , library available

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);// mpi communicator size = size of communicator , and it is a part of MPI_COMM_WORLD
//&world_size is total number of  or size , we give in mpirun -np 4 ./a.out


    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // &world_rank is id of process , it store address

if(world_rank%2==0)
{
    printf("Hello from process %d of %d\n", world_rank, world_size);
}

    MPI_Finalize();// all resourses free , mpi related environment closed
    printf("Hello\n");
    return 0;
}