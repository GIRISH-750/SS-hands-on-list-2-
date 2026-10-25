/*
 * Q51 (server): Communication between two machines using sockets.
 * Run the server on machine 1, and the client on machine 2 with
 * machine 1's IP address:  ./client <server-ip>
 * (On one machine, use 127.0.0.1 as the IP.)
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    // Allow reusing the port right after the server is restarted
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // accept connections on any interface
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }

    listen(server_fd, 5);
    printf("Server listening on port %d...\n", PORT);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    if (client_fd == -1) {
        perror("accept");
        return 1;
    }
    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

    char buf[100] = {0};
    read(client_fd, buf, sizeof(buf) - 1);
    printf("Client says: %s\n", buf);

    char reply[] = "Hello from the server!";
    write(client_fd, reply, strlen(reply));

    close(client_fd);
    close(server_fd);

    return 0;
}
