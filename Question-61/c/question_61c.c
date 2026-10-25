/*
 * Q61c: Catch SIGFPE using sigaction.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGFPE (signal %d) using sigaction\n", sig);
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    volatile int a = 10, b = 0;
    printf("Dividing by zero...\n");
    fflush(stdout);
    int c = a / b;

    printf("Result: %d\n", c);

    return 0;
}
