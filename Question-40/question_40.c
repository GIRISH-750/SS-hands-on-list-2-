/*
 * Q40: Print
 *   1. the maximum number of files a process can open
 *   2. the size of a pipe (its circular buffer)
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd[2];

    long max_files = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of open files per process: %ld\n", max_files);

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Total capacity of the pipe's circular buffer
    int pipe_size = fcntl(fd[1], F_GETPIPE_SZ);
    printf("Pipe size (circular buffer): %d bytes\n", pipe_size);

    // PIPE_BUF: max bytes that are guaranteed to be written atomically
    long pipe_buf = fpathconf(fd[1], _PC_PIPE_BUF);
    printf("PIPE_BUF (atomic write limit): %ld bytes\n", pipe_buf);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
