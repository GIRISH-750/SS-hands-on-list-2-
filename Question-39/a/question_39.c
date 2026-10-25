/*
 * Q39: Wait up to 10 seconds for data to be written into a FIFO,
 * using the select system call.
 *
 * The FIFO is opened with O_NONBLOCK so open() does not block
 * waiting for a writer. select() then does the waiting.
 * Run the writer (folder b) in another terminal within 10 seconds.
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>

#define FIFO_PATH "/tmp/q39_fifo"

int main() {
    char buf[100];

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    int fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    printf("Waiting up to 10 seconds for data in the FIFO...\n");

    int ret = select(fd + 1, &readfds, NULL, NULL, &tv);

    if (ret == -1) {
        perror("select");
    } else if (ret == 0) {
        printf("Timeout: no data was written within 10 seconds\n");
    } else {
        int n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("Data received: %s", buf);
        } else {
            printf("Writer closed without sending data\n");
        }
    }

    close(fd);

    return 0;
}
