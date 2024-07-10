#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 5
int arr[N];
long sum=0;
int i;

// race condition will be there


void* hello(void* threadId){
    long tid = (long)threadId; 
    sum=sum+tid;
    return NULL;
}

int main(){
    pthread_t t[N];
  
    for (long  i = 0; i < N; i++)
    {
        pthread_create(&t[i], NULL, hello, (void*) i);
    }

     for (long i = 0; i < N; i++){
        pthread_join(t[i], NULL);                 
    }
    
    printf("Sum is : %d", sum+N);
    return 0;
}