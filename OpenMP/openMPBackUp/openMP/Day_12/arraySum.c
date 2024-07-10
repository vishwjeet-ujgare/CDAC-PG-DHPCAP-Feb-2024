#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define arraSize 100

int main()
{

    int array[arraSize];
    int i,j,sum=0;

    int randomNumber = rand()% 1000 + 1;
   
   
    for(i=0; i<arraSize; i++)
    {
       array[i]=rand()%100+1;
    }

    //  printf("The random number is: %d\n", randomNumber);
   
    #pragma omp parallel 
    {
   
        #pragma omp atomic
        for(int j=0; j<arraSize; j++)
        {
        sum+=arraSize[j];
        }
      
        printf("Total Thread : %dln",omp_get_num_threads());
     }

    return 0;
}