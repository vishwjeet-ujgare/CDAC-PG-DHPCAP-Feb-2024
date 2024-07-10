#include<stdio.h>
#include <stdlib.h>
#include <time.h>


/* here, do your time-consuming job */

int main(){
    int n =1000000;
    float A[n],B[n];

    double start_time, end_time, measure_time;
    //Initialize array A and B on the (CPU)
    for(int i=0;i<n;++i){
        A[i]=i * 0.1f ;
        B[i]=i * 0.2f;
    }

    // Transfer data to device (GPU)
    #pragma acc enter data copyin(A,B)

    //First data region :Calculate element-wise sum(A+B) on device
    // start_time = omp_get_wtime();

    clock_t begin = clock();
    #pragma acc data present(A,B)
    {
        for( int i =0;i<n;++i){
            A[i]=A[i]+B[i];
        }
    }

    //Second data region : square each element of A on device (using present again)

    #pragma acc data present(A)
    {
        for( int i =0;i<n;++i){
            A[i]=A[i]*A[i];
        }
    }

    //  end_time = omp_get_wtime();
    clock_t end = clock();


    //   measure_time = end_time - start_time;
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    //Transfer final results in  A back to host

    #pragma acc exit data copyout(A)

    //print final result (noe accessible on the host)
    printf("Squared elements of (A+B):\n");
    for (int i=0;i<n;++i){
        printf("%f ",A[i]);
    }
    
    printf("\n");
        printf("Time taken for addition and  multiplication both: %f seconds\n", time_spent);
    return 0;
}
