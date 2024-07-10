#include<stdio.h>
#include<time.h>


#define N 1000
int array[N];
int main(){
    for (int i =0 ;i<N;i++){
        array[i]=i+1;
    }

    int sum = 0;

clock_t begin = clock();


    #pragma acc parallel loop reduction(+:sum) copyin(array[0:N])
    for (int i =0;i<N;i++){
        sum += array[i];
    }
/* here, do your time-consuming job */

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The sum of the array is :%d\n ",sum);
    printf("Time :%f\n ",time_spent);
    return 0;
}