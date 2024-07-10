#include<omp.h>
#include<stdio.h>

int main()
{
printf("No of thred proc %d:\n",omp_get_num_procs());
  int count=0;

  #pragma omp parallel 
  {
   

    #pragma omp atomic
    count++;

    #pragma omp single
    printf("Total Thread : %dln",omp_get_num_threads());
   
  }
  
  printf("Final count: %d\n",count);
    return 0;
}