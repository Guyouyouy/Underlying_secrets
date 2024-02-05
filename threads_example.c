#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *threadFunction1(void *arg) {
    printf("Thread 1 is running.\n");
    // 
    return NULL;
}


void *threadFunction2(void *arg) {
    printf("Thread 2 is running.\n");
    //
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    int ret;


    ret = pthread_create(&tid1, NULL, threadFunction1, NULL);
    if (ret != 0) {
        printf("Failed to create thread 1.\n");
        exit(1);
    }


    ret = pthread_create(&tid2, NULL, threadFunction2, NULL);
    if (ret != 0) {
        printf("Failed to create thread 2.\n");
        exit(1);
    }


    pthread_join(tid1, NULL);


    pthread_join(tid2, NULL);

    printf("Both threads finished.\n");

    return 0;
}