/*
 * Q59a: Catch SIGSEGV using signal().
 * We cause a segmentation fault by writing through a NULL pointer.
 * The handler must exit; returning would repeat the bad write forever.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGSEGV (signal %d): segmentation fault\n", sig);
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);

    int *p = NULL;
    printf("Writing to a NULL pointer...\n");
    fflush(stdout);
    *p = 10;

    return 0;
}
