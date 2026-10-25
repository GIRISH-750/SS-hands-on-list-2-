/*
 * Q49b: Protect shared memory from concurrent writes using a semaphore.
 * Only one process at a time can write into the shared memory.
 *
 * Demo: run in two terminals; the second one blocks until the
 * first one leaves the critical section.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t shmkey = ftok("/tmp", 'M');
    key_t semkey = ftok("/tmp", 'W');

    int shmid = shmget(shmkey, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    int semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(semkey, 1, 0);
    }
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    char *data = shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }

    struct sembuf lock = {0, -1, SEM_UNDO};
    struct sembuf unlock = {0, 1, SEM_UNDO};

    printf("Waiting to enter the critical section...\n");
    semop(semid, &lock, 1);
    printf("Inside the critical section\n");

    printf("Current data in shared memory: %s\n", data);

    printf("Enter new data to write: ");
    fflush(stdout);
    fgets(data, 1024, stdin);
    data[strcspn(data, "\n")] = '\0';

    printf("Written: %s\n", data);

    semop(semid, &unlock, 1);
    printf("Left the critical section\n");

    shmdt(data);

    return 0;
}
