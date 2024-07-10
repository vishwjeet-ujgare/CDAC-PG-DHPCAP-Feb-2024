#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arraySize 500
#define T 16

int *arr1;
int *arr2;
int *arr3; 

void *element_wise_addition(void *threadId) {
    long tid = (long) threadId;

    int chunk_size = arraySize / T;

    int start = tid * chunk_size;
    int end = (tid == T - 1) ? arraySize : (tid + 1) * chunk_size;

    for (int i = start; i < end; i++) {
        arr3[i] = arr1[i] + arr2[i];
    }

    return NULL;
}

int main() {

//declaration
    arr1= (int*)malloc(sizeof(int)* arraySize);
    arr2= (int*)malloc(sizeof(int)* arraySize);
    arr3= (int*)malloc(sizeof(int)* arraySize);

// allocation intialization
    for (int i = 0; i < arraySize; i++) {
        arr1[i] = i + 1;
        arr2[i] = i + 1;
        arr3[i]=0;
    }

    pthread_t *t;
    t = (pthread_t *) malloc(sizeof(pthread_t) * T);

    for (long i = 0; i < T; i++) {
        pthread_create(&t[i], NULL, element_wise_addition, (void *) i);
    }

    for (long i = 0; i < T; i++) {
        pthread_join(t[i], NULL);
    }

    printf("Element-wise sums:\n");
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    free(t);
    return 0;
}
