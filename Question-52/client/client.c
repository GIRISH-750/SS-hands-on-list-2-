/*
 * Q52 client: connects to the concurrent server and sends lines
 * typed by the user; the server echoes them back.
 * Usage: ./client <port> [server-ip]
 *   port 8081 -> fork server (52a)
 *   port 8082 -> thread server (52b)
 * Open several terminals and run several clients at the same time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port> [server-ip]\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    char *ip = (argc > 2) ? argv[2] : "127.0.0.1";

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }
    printf("Connected. Type messages (Ctrl+D to quit):\n");

    char buf[100];
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        write(fd, buf, strlen(buf));

        int n = read(fd, buf, sizeof(buf) - 1);
        if (n <= 0) {
            break;
        }
        buf[n] = '\0';
        printf("Echo from server: %s", buf);
    }

    close(fd);

    return 0;
}
