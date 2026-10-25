/*
 * Q61a: Catch SIGSEGV using sigaction.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGSEGV (signal %d) using sigaction\n", sig);
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);   // block no extra signals while in the handler
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    printf("Writing to a NULL pointer...\n");
    fflush(stdout);
    *p = 10;

    return 0;
}
