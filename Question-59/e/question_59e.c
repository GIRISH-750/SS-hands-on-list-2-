/*
 * Q59e: Catch SIGALRM using setitimer (ITIMER_REAL).
 * ITIMER_REAL counts real time and sends SIGALRM.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig) {
    printf("Caught SIGALRM (signal %d) from setitimer(ITIMER_REAL)\n", sig);
}

int main() {
    signal(SIGALRM, handler);

    struct itimerval timer = {0};
    timer.it_value.tv_sec = 3;   // fire once after 3 seconds

    setitimer(ITIMER_REAL, &timer, NULL);
    printf("ITIMER_REAL set for 3 seconds, waiting...\n");

    pause();

    return 0;
}
