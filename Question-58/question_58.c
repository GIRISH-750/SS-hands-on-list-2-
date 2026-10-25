/*
 * Q58: Create three threads and print their IDs.
 * Compile: gcc question_58.c -o question_58 -pthread
 */
#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    int num = *(int *)arg;
    printf("Thread %d: my ID is %lu\n", num, (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t tid[3];
    int num[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, thread_func, &num[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
        printf("Main: thread %d had ID %lu\n", i + 1, (unsigned long)tid[i]);
    }

    return 0;
}
