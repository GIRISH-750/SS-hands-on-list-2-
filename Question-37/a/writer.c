/*
 * Q37 (program 1 - writer): One-way communication through a FIFO.
 * Run the reader in another terminal.
 * open() blocks until the other side also opens the FIFO.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/q37_fifo"

int main() {
    char buf[100];

    // Create the FIFO (ignore the error if it already exists)
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Enter a message: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);

    write(fd, buf, strlen(buf) + 1);
    printf("Message sent\n");

    close(fd);

    return 0;
}
