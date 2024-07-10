#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 30000
#define T 16

pthread_mutex_t mutex; // create mutex variable
long sum=0;
int arr[N];



void *hello(void* threadId){
    long tid = (long)threadId;
    long localSum = 0;

    int chunk_size = N/T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;

    if (tid == T - 1){
        end = N;
    }

    for (int i = start; i < end; i++)
    {
        localSum+=(long)arr[i];
    }
    

    pthread_mutex_lock(&mutex); //give lock
    sum += localSum;
    pthread_mutex_unlock(&mutex); //unlock
    return NULL;
}

int main(){
    pthread_t* t;

    for (int i = 0; i < N; i++)
    {
        arr[i] = i;
    }
    

    pthread_mutex_init(&mutex, NULL); // mutex initialize in main() funtion
    t = malloc(sizeof(pthread_t) * N);  //dynamic mem allocation , because heap mem greater than stack

    for (long  i = 0; i < T; i++)
        pthread_create(&t[i], NULL, hello, (void*) i);
    

     for (long i = 0; i < T; i++)
        pthread_join(t[i], NULL);                 


    pthread_mutex_destroy(&mutex); // destroy the lock
    
    printf("Sum is : %d \n", sum+N);
    printf("Expected sum : %d \n", N*(N+1)/2);

    free(t);
    return 0;
}