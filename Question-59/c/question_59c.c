/*
 * Q59c: Catch SIGFPE using signal().
 * Integer division by zero raises SIGFPE.
 * The handler must exit; returning would repeat the division forever.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGFPE (signal %d): division by zero\n", sig);
    exit(1);
}

int main() {
    signal(SIGFPE, handler);

    volatile int a = 10, b = 0;   // volatile: stop the compiler optimizing it away
    printf("Dividing by zero...\n");
    fflush(stdout);
    int c = a / b;

    printf("Result: %d\n", c);

    return 0;
}
