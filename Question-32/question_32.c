/*
 * Q32: Send data from the parent process to the child process
 * using a pipe.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child: only reads, so close the write end
        close(fd[1]);

        read(fd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);

        close(fd[0]);
    } else {
        // Parent: only writes, so close the read end
        close(fd[0]);

        char msg[] = "Hello child, this is your parent!";
        write(fd[1], msg, strlen(msg) + 1);
        printf("Parent sent: %s\n", msg);

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
