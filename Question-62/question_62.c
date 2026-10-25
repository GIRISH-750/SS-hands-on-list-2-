/*
 * Q62: Ignore SIGINT, then reset it to the default action,
 * using the sigaction system call.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT is IGNORED for 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5);

    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
    printf("\nSIGINT reset to DEFAULT. Press Ctrl+C now to terminate the program.\n");
    sleep(5);

    printf("No Ctrl+C pressed. Exiting normally.\n");

    return 0;
}
