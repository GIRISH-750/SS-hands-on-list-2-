/*
 * Q59d: Catch SIGALRM using the alarm system call.
 * alarm(3) sends SIGALRM to the process after 3 seconds.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGALRM (signal %d) from alarm()\n", sig);
}

int main() {
    signal(SIGALRM, handler);

    alarm(3);
    printf("Alarm set for 3 seconds, waiting...\n");

    pause();

    return 0;
}
