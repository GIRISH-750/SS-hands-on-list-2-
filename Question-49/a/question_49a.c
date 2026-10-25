/*
 * Q49a: Ticket number program (from list 1) rewritten with a semaphore.
 * The semaphore makes "read ticket -> increment -> write ticket"
 * a critical section, so two processes never get the same number.
 *
 * Demo: run this in two terminals. While the first one waits for
 * Enter (inside the critical section), the second one blocks.
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("/tmp", 'T');

    // Try to create the semaphore. If we created it, set it to 1.
    // If it already exists, just get its ID.
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0);
    }
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    int fd = open("ticket.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct sembuf lock = {0, -1, SEM_UNDO};     // P (wait)
    struct sembuf unlock = {0, 1, SEM_UNDO};    // V (signal)

    printf("Waiting to enter the critical section...\n");
    semop(semid, &lock, 1);
    printf("Inside the critical section\n");

    int ticket = 0;
    lseek(fd, 0, SEEK_SET);
    if (read(fd, &ticket, sizeof(ticket)) != sizeof(ticket)) {
        ticket = 0;   // empty file: first ticket
    }

    ticket++;

    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket, sizeof(ticket));
    printf("New ticket number: %d\n", ticket);

    printf("Press Enter to leave the critical section...");
    getchar();

    semop(semid, &unlock, 1);
    printf("Left the critical section\n");

    close(fd);

    return 0;
}
