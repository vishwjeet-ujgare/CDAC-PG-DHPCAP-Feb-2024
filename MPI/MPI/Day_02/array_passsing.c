#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#define N 50

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int myid;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int myarray[N];

    // Process with ID exactly equla to 0
    if (myid == 0)
    {
        int i = 0;

        printf("\nmy id %d My array: ", myid);
        while (i < N)
        {
            myarray[i] = i + 1;
            // printf(" %d ", myarray[i]);
            i++;
        }

        MPI_Send(myarray, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("\nmyid : %d \t Data send \n", myid);
    }
    else if (myid == 1)
    {
        int myarray1[N];
        int i = 0;

        MPI_Recv(myarray1, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nmyid %d \t Data received .", myid);

        printf("\nmy id %d My array: ", myid);
        while(i < N)
        {
            printf(" %d ", myarray1[i]);
            i++;
        }

        printf("\n\n Program exit !");
    }

    MPI_Finalize();

    return 0;
}