/*
 * Q38 (program 2): Two-way communication using two FIFOs.
 *   reads from fifo1, replies on fifo2
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

    int rfd = open(FIFO1, O_RDONLY);
    int wfd = open(FIFO2, O_WRONLY);
    if (rfd == -1 || wfd == -1) {
        perror("open");
        return 1;
    }

    read(rfd, buf, sizeof(buf));
    printf("Program 2 received: %s", buf);

    printf("Program 2 - enter reply: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    write(wfd, buf, strlen(buf) + 1);

    close(rfd);
    close(wfd);

    return 0;
}
