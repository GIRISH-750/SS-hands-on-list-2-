/*
 * Q34a: Execute "ls -l | wc" using dup.
 * dup(fd) returns the LOWEST free descriptor, so we first
 * close 1 (or 0) and then call dup to make it take that slot.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    if (fork() == 0) {
        // Child 1: ls -l, stdout -> pipe write end
        close(1);
        dup(fd[1]);          // gets fd 1 (lowest free)
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        return 1;
    }

    if (fork() == 0) {
        // Child 2: wc, stdin <- pipe read end
        close(0);
        dup(fd[0]);          // gets fd 0 (lowest free)
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        return 1;
    }

    // Parent must close both ends, otherwise wc never sees EOF
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
