/*
 * Q60: Ignore SIGINT, then reset it to the default action,
 * using the signal system call.
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is IGNORED for 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("\nSIGINT reset to DEFAULT. Press Ctrl+C now to terminate the program.\n");
    sleep(5);

    printf("No Ctrl+C pressed. Exiting normally.\n");

    return 0;
}
