/*
 * Q53b: Interval timer with ITIMER_VIRTUAL (10 s + 10 us).
 * ITIMER_VIRTUAL counts only the time the process runs in USER mode,
 * and sends SIGVTALRM. So the process must keep the CPU busy;
 * if it slept, the timer would never expire.
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
    char msg[] = "SIGVTALRM received (ITIMER_VIRTUAL expired)\n";
    write(1, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGVTALRM, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL set for 10 seconds and 10 microseconds\n");
    fflush(stdout);

    // Busy loop: uses CPU in user mode
    while (1) {
    }

    return 0;
}
