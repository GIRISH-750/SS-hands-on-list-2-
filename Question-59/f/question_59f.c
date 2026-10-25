/*
 * Q59f: Catch SIGVTALRM using setitimer (ITIMER_VIRTUAL).
 * ITIMER_VIRTUAL counts only user-mode CPU time, so we must
 * keep the CPU busy until the signal arrives.
 */
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

volatile sig_atomic_t caught = 0;

void handler(int sig) {
    (void)sig;
    caught = 1;
}

int main() {
    signal(SIGVTALRM, handler);

    struct itimerval timer = {0};
    timer.it_value.tv_sec = 3;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    printf("ITIMER_VIRTUAL set for 3 seconds of CPU time, busy looping...\n");

    while (!caught) {
    }

    printf("Caught SIGVTALRM (signal %d) from setitimer(ITIMER_VIRTUAL)\n", SIGVTALRM);

    return 0;
}
