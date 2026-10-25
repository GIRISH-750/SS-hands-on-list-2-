/*
 * Q34c: Execute "ls -l | wc" using fcntl.
 * fcntl(fd, F_DUPFD, n) returns the lowest free descriptor >= n.
 * After closing 1 (or 0), asking for >= 1 (or >= 0) gives us exactly that fd.
 */
#include <stdio.h>
#include <fcntl.h>
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
        fcntl(fd[1], F_DUPFD, 1);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        return 1;
    }

    if (fork() == 0) {
        // Child 2: wc, stdin <- pipe read end
        close(0);
        fcntl(fd[0], F_DUPFD, 0);
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
