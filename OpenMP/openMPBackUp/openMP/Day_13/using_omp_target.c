#include<stdio.h>
#include<time.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#define N 3



int  main(){
int A[N];
int B[N];
int C[N];


for(int i=0;i<N;i++){
    A[i]=2;
    B[i]=4;
    C[i]=0;
}
 


#pragma omp target map(to:A[0:N]) map(to:B[0:N]) map(from:C[0:N])
    {
        for(int i=0;i<N;i++){
            C[i]=A[i]+B[i];
        }
    }

//print the whole array
for(int i=0;i<N;i++){
    printf(" A[%d]+B[%d] = %d \n",i,i,C[i]);
}

}



 