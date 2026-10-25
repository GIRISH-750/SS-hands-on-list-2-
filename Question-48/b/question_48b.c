/*
 * Q48b: Create a counting semaphore and initialize it.
 * A counting semaphore can be any value >= 0 (e.g. number of free resources).
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("/tmp", 'C');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 5;   // counting semaphore: 5 resources available

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        return 1;
    }

    printf("Counting semaphore created. ID: %d, value: %d\n",
           semid, semctl(semid, 0, GETVAL));

    return 0;
}
