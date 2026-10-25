/*
 * Q49d: Remove the semaphores created in Q49 a, b and c
 * (and the shared memory used in Q49b).
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

void remove_sem(char id, const char *name) {
    int semid = semget(ftok("/tmp", id), 1, 0);
    if (semid == -1) {
        printf("%s semaphore does not exist\n", name);
        return;
    }
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        return;
    }
    printf("%s semaphore (ID %d) removed\n", name, semid);
}

int main() {
    remove_sem('T', "Ticket (49a)");
    remove_sem('W', "Shared memory (49b)");
    remove_sem('R', "Counting (49c)");

    int shmid = shmget(ftok("/tmp", 'M'), 0, 0);
    if (shmid != -1 && shmctl(shmid, IPC_RMID, NULL) == 0) {
        printf("Shared memory of 49b (ID %d) removed\n", shmid);
    }

    printf("Check with 'ipcs -s' and 'ipcs -m'\n");

    return 0;
}
