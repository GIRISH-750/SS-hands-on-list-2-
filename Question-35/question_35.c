/*
 * Q35: Count directories in the current directory using
 *      ls -l | grep ^d | wc
 * Only dup2 is used. Three processes, two pipes:
 *   ls -l  --(p1)-->  grep ^d  --(p2)-->  wc
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2];

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe");
        return 1;
    }

    if (fork() == 0) {
        // ls -l : stdout -> p1
        dup2(p1[1], 1);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        return 1;
    }

    if (fork() == 0) {
        // grep ^d : stdin <- p1, stdout -> p2
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep");
        return 1;
    }

    if (fork() == 0) {
        // wc : stdin <- p2
        dup2(p2[0], 0);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        return 1;
    }

    // Parent closes everything so each reader gets EOF
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
