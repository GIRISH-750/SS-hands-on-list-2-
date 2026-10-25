/*
 * Q50: Deadlock using semaphores.
 *
 * Two semaphores A and B (both 1 = free).
 *   Parent: locks A, waits a bit, then tries to lock B
 *   Child : locks B, waits a bit, then tries to lock A
 * Each holds what the other needs, so both wait forever: deadlock.
 *
 * Press Ctrl+C to stop. The parent then removes the semaphores.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int semid;
pid_t child;

void cleanup(int sig) {
    (void)sig;
    kill(child, SIGKILL);
    semctl(semid, 0, IPC_RMID);
    printf("\nSemaphores removed. Exiting.\n");
    exit(0);
}

void lock(int num) {
    struct sembuf op = {num, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        exit(0);   // semaphores were removed
    }
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);   // print immediately (no buffering)

    // A set with 2 semaphores: 0 = A, 1 = B
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    semctl(semid, 1, SETVAL, arg);

    fflush(stdout);
    child = fork();

    if (child == 0) {
        signal(SIGINT, SIG_DFL);   // child just dies on Ctrl+C
        lock(1);
        printf("Child: locked B\n");
        sleep(1);
        printf("Child: waiting for A...\n");
        lock(0);
        printf("Child: locked A (will never print)\n");
        return 0;
    }

    signal(SIGINT, cleanup);

    lock(0);
    printf("Parent: locked A\n");
    sleep(1);
    printf("Parent: waiting for B...\n");
    lock(1);
    printf("Parent: locked B (will never print)\n");

    wait(NULL);

    return 0;
}
