#include<pthread.h>

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 10

// #intialize an array of size N and assign each thread to prin elemtn which is swaul to their threadID


int* array[N];

void* hello(void* threadId){
     long tid = (long)threadId;
     
     array[tid]=threadId;
     
     printf("Thread %d is printing %d \n",threadId,array[tid]);
     
     
     return NULL;
}

int main(){

    pthread_t t[N];

    long i ;

    //  for(int j = 0;j<N;j++)
    // {
    //    array[j]=j;
    // }

    
    for( i = 0;i<N;i++)
    {
        pthread_create(&t[i],NULL,hello,(void*)i);
    }

    for( i =0;i<N;i++){
        pthread_join(t[i],NULL);
    }


  


    return 0;


}