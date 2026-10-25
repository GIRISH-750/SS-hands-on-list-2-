/*
 * Q39 helper: writes one line into the FIFO, so the select
 * program (folder a) has something to read.
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/q39_fifo"

int main() {
    char buf[100];

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open (start the reader in folder a first)");
        return 1;
    }

    printf("Enter a message: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);

    write(fd, buf, strlen(buf));

    close(fd);

    return 0;
}
