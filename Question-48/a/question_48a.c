/*
 * Q48a: Create a binary semaphore and initialize it.
 * A binary semaphore has value 0 or 1 (like a lock).
 *
 * On Linux we must define union semun ourselves for semctl.
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
    key_t key = ftok("/tmp", 'B');
    int semid = semget(key, 1, IPC_CREAT | 0666);   // 1 semaphore in the set
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 1;   // binary semaphore: starts as "unlocked"

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        return 1;
    }

    printf("Binary semaphore created. ID: %d, value: %d\n",
           semid, semctl(semid, 0, GETVAL));

    return 0;
}
