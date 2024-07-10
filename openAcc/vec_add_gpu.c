#include <stdio.h>
#include <stdlib.h>

#define N 100

void vecaddgpu( float *restrict r, float *a, float *b, int n ) {
    #pragma acc kernels loop copyin(a[0:n]) copyout(r[0:n])
    for ( int i = 0; i < n; ++i) r[i] = a[i] + b[i];
}

int main ( int argc, char* argv[] ) {
    float * a; /* input vector 1 */
    float * b; /* input vector 2 */
    float * r; /* output vector */
    float * e; /* expected output values */
    int i, errs;
    a = (float*) malloc( N*sizeof(float) );
    b = (float*) malloc( N*sizeof(float) );
    r = (float*) malloc( N*sizeof(float) );
    e = (float*) malloc( N*sizeof(float) );

    for ( i = 0; i < N; ++i)
    {
        a[i] = (float)(i+1);
        b[i] = (float) (1000*i);
    }
    /* compute on the GPU */
    vecaddgpu( r, a, b, N);
    /* compute on the host to compare */
    for( i = 0; i < N; ++i) e[i] = a[i] + b[i];
    /* compare results */
    errs = 0;
    for(i=0; i < N; ++i) {
        if ( r[i] != e[i])
        {
            ++errs;
        }
    }

    printf("%d errors found\n", errs);
    return errs;
    
    

}


//gcc vec_add_gpu.c -o vec_add -fopenacc
//./vec_add
