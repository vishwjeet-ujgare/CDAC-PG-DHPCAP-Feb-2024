#include<stdio.h>
#include <stdlib.h>

#define N 5

int main()
{
int A[N][N],B[N][N], C[N][N];
 for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100; 
            B[i][j] = rand() % 100;
        }
    }


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }



    for (int i = 0; i < N; i++) {
            printf("%d, ",C[i][i]);
      
    }




}