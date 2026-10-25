/*
 * Q61b: Catch SIGINT using sigaction.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nCaught SIGINT (signal %d) using sigaction\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C...\n");
    pause();

    printf("Program continues normally after the handler\n");

    return 0;
}
