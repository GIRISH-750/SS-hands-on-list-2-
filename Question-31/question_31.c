/*
 * Q31: Create a pipe, write to it, read from it,
 * and display the content on the monitor.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd[2];
    char msg[] = "Hello through the pipe!";
    char buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // fd[1] is the write end, fd[0] is the read end
    write(fd[1], msg, strlen(msg) + 1);

    read(fd[0], buf, sizeof(buf));

    printf("Read from pipe: %s\n", buf);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
