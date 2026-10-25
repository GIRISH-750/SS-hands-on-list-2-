/*
 * Q53a: Interval timer with ITIMER_REAL (10 s + 10 us).
 * ITIMER_REAL counts real (wall-clock) time and sends SIGALRM.
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
    char msg[] = "SIGALRM received (ITIMER_REAL expired)\n";
    write(1, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGALRM, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 10;       // first expiry after 10 s + 10 us
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;    // then every 10 s + 10 us
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL set for 10 seconds and 10 microseconds\n");
    fflush(stdout);

    // Real time passes even while sleeping, so pause() is enough
    while (1) {
        pause();
    }

    return 0;
}
