/*
 * Q52b: Concurrent server using pthread_create.
 * For every client, the server creates a new thread to handle it.
 * Compile: gcc question_52b.c -o question_52b -pthread
 * Test with the client in Question-52/client (port 8082).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8082

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    char buf[100];
    int n;

    while ((n = read(client_fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("[Thread %lu] Client says: %s", (unsigned long)pthread_self(), buf);
        write(client_fd, buf, n);
    }

    printf("[Thread %lu] Client disconnected\n", (unsigned long)pthread_self());
    close(client_fd);

    return NULL;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);   // print immediately (no buffering)

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
    printf("Concurrent server (threads) listening on port %d...\n", PORT);

    while (1) {
        // Give each thread its own copy of the fd (heap), so the next
        // accept() cannot overwrite it before the thread reads it
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd == -1) {
            perror("accept");
            free(client_fd);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_fd);
        pthread_detach(tid);   // thread cleans itself up when done
    }

    return 0;
}
