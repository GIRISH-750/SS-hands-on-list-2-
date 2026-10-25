/*
 * Q47: Shared memory operations
 *   a. Write some data to shared memory
 *   b. Attach read-only (SHM_RDONLY) and try to overwrite
 *   c. Detach the shared memory
 *   d. Remove the shared memory
 *
 * Note: for shared memory the read-only flag is SHM_RDONLY
 * (O_RDONLY is the flag for open()).
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    key_t key = ftok("/tmp", 'S');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // a. Attach normally (read-write) and write data
    char *data = shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }
    strcpy(data, "Hello from shared memory!");
    printf("a. Written: %s\n", data);

    // b. Attach read-only and try to overwrite.
    //    Writing to read-only memory gives SIGSEGV, so we do it in a
    //    child process. That way only the child crashes, not this program.
    fflush(stdout);   // so the child does not print our buffered output again
    pid_t pid = fork();
    if (pid == 0) {
        char *ro = shmat(shmid, NULL, SHM_RDONLY);
        if (ro == (char *)-1) {
            perror("shmat SHM_RDONLY");
            return 1;
        }
        printf("b. Read-only attach, reading: %s\n", ro);
        printf("b. Trying to overwrite...\n");
        fflush(stdout);
        strcpy(ro, "Overwritten!");     // causes SIGSEGV
        printf("b. Overwrite worked (should not happen)\n");
        return 0;
    }

    int status;
    wait(&status);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
        printf("b. Child got SIGSEGV: cannot overwrite read-only shared memory\n");
    }
    printf("b. Data is still: %s\n", data);

    // c. Detach
    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }
    printf("c. Shared memory detached\n");

    // d. Remove
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        return 1;
    }
    printf("d. Shared memory removed (check with 'ipcs -m')\n");

    return 0;
}
