/*
 * Q53c: Interval timer with ITIMER_PROF (10 s + 10 us).
 * ITIMER_PROF counts time in USER + KERNEL mode,
 * and sends SIGPROF. The process must keep the CPU busy.
 * Press Ctrl+C to stop.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig) {
    (void)sig;
    // write() is used instead of printf() because it is safe inside a
    // signal handler and prints immediately (no buffering)
    char msg[] = "SIGPROF received (ITIMER_PROF expired)\n";
    write(1, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGPROF, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF set for 10 seconds and 10 microseconds\n");
    fflush(stdout);

    while (1) {
    }

    return 0;
}
