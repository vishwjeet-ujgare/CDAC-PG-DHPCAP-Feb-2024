#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 300000
pthread_mutex_t mutex; // create mutex variable
long sum=0;


void* hello(void* threadId){
    long tid = (long)threadId;
    pthread_mutex_lock(&mutex); //give lock
    sum += tid;
    pthread_mutex_unlock(&mutex); //unlock
    return NULL;
}

int main(){
    pthread_t* t;

    pthread_mutex_init(&mutex, NULL); // mutex initialize in main() funtion
    t = malloc(sizeof(pthread_t) * N);  //dynamic mem allocation , because heap mem greater than stack

    for (long  i = 0; i < N; i++)
        pthread_create(&t[i], NULL, hello, (void*) i);
    

     for (long i = 0; i < N; i++)
        pthread_join(t[i], NULL);                 


    pthread_mutex_destroy(&mutex); // destroy the lock
    
    printf("Sum is : %d \n", sum+N);
    // printf("Expected sum : %d \n", N*(N+1)/2);

    free(t);
    return 0;
}