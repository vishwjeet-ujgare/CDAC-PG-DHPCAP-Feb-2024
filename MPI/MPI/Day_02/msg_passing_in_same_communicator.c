#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int myid;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int myval;

    //Process with ID exactly equla to 0
    if(myid == 0){
        myval = 100;

        printf("\n myid : %d \t myval = %d ",myid,myval);

        MPI_Send(&myval,1,MPI_INT,1,0,MPI_COMM_WORLD);

        printf("\n myid : %d \t Data send \n",myid);

    }else if(myid == 1) {
        int a = 200;
        myval=300;

        MPI_Recv( &a, 1 ,MPI_INT,0 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        printf("\n myid %d \t Data received .",myid);

        printf("\n myid : %d \t a = %d",myid,a);
        printf("\n myid : %d \t myval = %d",myid,myval);
        printf("\n\n Program exit !");
    }


    MPI_Finalize();

    return 0;
}