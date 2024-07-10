#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#define N 16

void* hello(void* threadId){
    long tid = (long)threadId;
    printf("Forking %ld of %d \n",tid,N);
    sleep(1);
    printf("Joining %ld of %d \n",tid,N);
    return NULL;
}


int main (){
    pthread_t t[N];

long i ;
    for( i = 0;i<N;i++)
    {
        pthread_create(&t[i],NULL,hello,(void*)i);
    }

    for( i =0;i<N;i++){
        pthread_join(t[i],NULL);
    }

    return 0;
}