/*
 * Q49c: Protect two pseudo resources with a counting semaphore.
 * The semaphore starts at 2 (two resources free).
 * Each process takes one resource (P), uses it, then gives it back (V).
 *
 * Demo: run in three terminals. Two get a resource right away;
 * the third blocks until one of them presses Enter.
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("/tmp", 'R');

    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        union semun arg;
        arg.val = 2;   // two resources
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0);
    }
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    struct sembuf take = {0, -1, SEM_UNDO};
    struct sembuf give = {0, 1, SEM_UNDO};

    printf("Free resources: %d. Waiting for a resource...\n",
           semctl(semid, 0, GETVAL));

    semop(semid, &take, 1);
    printf("Got a resource. Free resources left: %d\n",
           semctl(semid, 0, GETVAL));

    printf("Using the resource. Press Enter to release it...");
    getchar();

    semop(semid, &give, 1);
    printf("Resource released. Free resources: %d\n",
           semctl(semid, 0, GETVAL));

    return 0;
}
