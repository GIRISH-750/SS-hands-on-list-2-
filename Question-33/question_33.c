/*
 * Q33: Two-way communication between parent and child.
 * A pipe is one-way, so we use two pipes:
 *   p2c: parent -> child
 *   c2p: child  -> parent
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p2c[2], c2p[2];
    char buf[100];

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child: reads from p2c, writes to c2p
        close(p2c[1]);
        close(c2p[0]);

        read(p2c[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);

        char reply[] = "Hi parent, message received!";
        write(c2p[1], reply, strlen(reply) + 1);

        close(p2c[0]);
        close(c2p[1]);
    } else {
        // Parent: writes to p2c, reads from c2p
        close(p2c[0]);
        close(c2p[1]);

        char msg[] = "Hello child!";
        write(p2c[1], msg, strlen(msg) + 1);

        read(c2p[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);

        close(p2c[1]);
        close(c2p[0]);
        wait(NULL);
    }

    return 0;
}
