/*
 * Q59b: Catch SIGINT using signal().
 * Press Ctrl+C: instead of being killed, the program runs the handler.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nCaught SIGINT (signal %d)\n", sig);
}

int main() {
    signal(SIGINT, handler);

    printf("Press Ctrl+C...\n");
    pause();   // wait until a signal arrives

    printf("Program continues normally after the handler\n");

    return 0;
}
