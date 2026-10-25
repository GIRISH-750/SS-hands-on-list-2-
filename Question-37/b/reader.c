/*
 * Q37 (program 2 - reader): One-way communication through a FIFO.
 * Run the writer in another terminal.
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/q37_fifo"

int main() {
    char buf[100];

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    read(fd, buf, sizeof(buf));
    printf("Message received: %s", buf);

    close(fd);

    return 0;
}
