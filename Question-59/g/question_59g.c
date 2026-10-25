/*
 * Q59g: Catch SIGPROF using setitimer (ITIMER_PROF).
 * ITIMER_PROF counts user + kernel CPU time, so we must
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
    signal(SIGPROF, handler);

    struct itimerval timer = {0};
    timer.it_value.tv_sec = 3;

    setitimer(ITIMER_PROF, &timer, NULL);
    printf("ITIMER_PROF set for 3 seconds of CPU time, busy looping...\n");

    while (!caught) {
    }

    printf("Caught SIGPROF (signal %d) from setitimer(ITIMER_PROF)\n", SIGPROF);

    return 0;
}
