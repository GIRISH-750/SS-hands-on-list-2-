/*
 * Q34b: Execute "ls -l | wc" using dup2.
 * dup2(old, new) closes "new" (if open) and makes it a copy of "old".
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
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        return 1;
    }

    if (fork() == 0) {
        // Child 2: wc, stdin <- pipe read end
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        return 1;
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
