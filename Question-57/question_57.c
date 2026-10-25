/*
 * Q57: Print system limits using sysconf.
 */
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("a. Max length of arguments to exec: %ld bytes\n", sysconf(_SC_ARG_MAX));
    printf("b. Max processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Clock ticks (jiffies) per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. Max number of open files: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. Page size: %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("f. Total pages in physical memory: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. Available pages in physical memory: %ld\n", sysconf(_SC_AVPHYS_PAGES));

    return 0;
}
