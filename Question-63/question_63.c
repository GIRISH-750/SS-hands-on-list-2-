/*
 * Q63: Create an orphan process.
 * The child kills its parent with SIGKILL. The child keeps running
 * without a parent (an orphan), and is adopted by init (PID 1)
 * or by a "subreaper" process such as systemd --user.
 * You can see this because getppid() changes.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: my PID = %d, my parent PID = %d\n", getpid(), getppid());

        sleep(1);
        printf("Child: sending SIGKILL to parent %d\n", getppid());
        kill(getppid(), SIGKILL);

        sleep(1);
        printf("Child: now I am an orphan, my new parent PID = %d\n", getppid());

        return 0;
    }

    printf("Parent: my PID = %d, waiting...\n", getpid());
    while (1) {
        pause();   // parent waits here until it is killed
    }

    return 0;
}
