/*
 * Q55: Set a system resource limit using setrlimit.
 * Here we lower the soft limit on the number of open files
 * (RLIMIT_NOFILE) and print it before and after.
 * A normal user can lower limits, and raise the soft limit
 * only up to the hard limit.
 */
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit lim;

    getrlimit(RLIMIT_NOFILE, &lim);
    printf("Before: soft = %llu, hard = %llu\n",
           (unsigned long long)lim.rlim_cur, (unsigned long long)lim.rlim_max);

    lim.rlim_cur = 100;   // new soft limit

    if (setrlimit(RLIMIT_NOFILE, &lim) == -1) {
        perror("setrlimit");
        return 1;
    }

    getrlimit(RLIMIT_NOFILE, &lim);
    printf("After:  soft = %llu, hard = %llu\n",
           (unsigned long long)lim.rlim_cur, (unsigned long long)lim.rlim_max);

    return 0;
}
