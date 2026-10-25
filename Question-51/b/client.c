/*
 * Q51 (client): Connects to the server and exchanges a message.
 * Usage: ./client <server-ip> [port]
 *        (default IP 127.0.0.1, default port 8080)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    char *ip = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 8080;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
        printf("Invalid IP address: %s\n", ip);
        return 1;
    }

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }
    printf("Connected to %s:%d\n", ip, port);

    char msg[] = "Hello from the client!";
    write(fd, msg, strlen(msg));

    char buf[100] = {0};
    read(fd, buf, sizeof(buf) - 1);
    printf("Server says: %s\n", buf);

    close(fd);

    return 0;
}
