/*
 * Q38 (program 1): Two-way communication using two FIFOs.
 *   fifo1: program1 -> program2
 *   fifo2: program2 -> program1
 * Both programs open the FIFOs in the SAME order (fifo1 first),
 * otherwise each would block forever waiting for the other (deadlock).
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/q38_fifo1"
#define FIFO2 "/tmp/q38_fifo2"

int main() {
    char buf[100];

    if ((mkfifo(FIFO1, 0666) == -1 && errno != EEXIST) ||
        (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST)) {
        perror("mkfifo");
        return 1;
    }

    int wfd = open(FIFO1, O_WRONLY);
    int rfd = open(FIFO2, O_RDONLY);
    if (wfd == -1 || rfd == -1) {
        perror("open");
        return 1;
    }

    printf("Program 1 - enter message: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    write(wfd, buf, strlen(buf) + 1);

    read(rfd, buf, sizeof(buf));
    printf("Program 1 received: %s", buf);

    close(wfd);
    close(rfd);

    return 0;
}
