/*
 * Q64 (program 1): Try to catch SIGSTOP, then wait for it.
 * Run this first, then run the sender (folder b) with this PID.
 *
 * Result: SIGSTOP (like SIGKILL) can NOT be caught, blocked or ignored.
 * signal() fails with EINVAL, and when SIGSTOP arrives the process
 * is simply stopped by the kernel; the handler never runs.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d (this never happens for SIGSTOP)\n", sig);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);   // print immediately

    if (signal(SIGSTOP, handler) == SIG_ERR) {
        perror("signal(SIGSTOP)");
        printf("=> SIGSTOP cannot be caught\n");
    }

    printf("My PID is %d. Waiting for SIGSTOP...\n", getpid());

    for (int i = 1; ; i++) {
        printf("Running... %d\n", i);
        sleep(1);
    }

    return 0;
}
