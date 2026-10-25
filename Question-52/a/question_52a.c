/*
 * Q52a: Concurrent server using fork.
 * For every client, the server forks a child to handle it,
 * and the parent goes back to accept() the next client.
 * Test with the client in Question-52/client (port 8081).
 */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081

void handle_client(int client_fd) {
    char buf[100];
    int n;

    // Echo back everything the client sends, until it disconnects
    while ((n = read(client_fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("[PID %d] Client says: %s", getpid(), buf);
        write(client_fd, buf, n);
    }

    printf("[PID %d] Client disconnected\n", getpid());
    close(client_fd);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);   // print immediately (no buffering)

    // Children are cleaned up automatically, so no zombies are left
    signal(SIGCHLD, SIG_IGN);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }

    listen(server_fd, 5);
    printf("Concurrent server (fork) listening on port %d...\n", PORT);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        if (fork() == 0) {
            // Child: does not need the listening socket
            close(server_fd);
            handle_client(client_fd);
            return 0;
        }

        // Parent: does not need the client socket
        close(client_fd);
    }

    return 0;
}
