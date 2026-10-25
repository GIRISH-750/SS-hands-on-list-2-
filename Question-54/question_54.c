/*
 * Q54: Print system resource limits using getrlimit.
 * Each limit has a soft limit (current) and a hard limit (maximum).
 */
#include <stdio.h>
#include <sys/resource.h>

void print_limit(int resource, const char *name) {
    struct rlimit lim;

    if (getrlimit(resource, &lim) == -1) {
        perror("getrlimit");
        return;
    }

    printf("%-18s soft = ", name);
    if (lim.rlim_cur == RLIM_INFINITY) {
        printf("%-12s", "unlimited");
    } else {
        printf("%-12llu", (unsigned long long)lim.rlim_cur);
    }

    printf(" hard = ");
    if (lim.rlim_max == RLIM_INFINITY) {
        printf("unlimited\n");
    } else {
        printf("%llu\n", (unsigned long long)lim.rlim_max);
    }
}

int main() {
    print_limit(RLIMIT_AS, "RLIMIT_AS");             // virtual memory size
    print_limit(RLIMIT_CORE, "RLIMIT_CORE");         // core file size
    print_limit(RLIMIT_CPU, "RLIMIT_CPU");           // CPU time (seconds)
    print_limit(RLIMIT_DATA, "RLIMIT_DATA");         // data segment size
    print_limit(RLIMIT_FSIZE, "RLIMIT_FSIZE");       // max file size
    print_limit(RLIMIT_LOCKS, "RLIMIT_LOCKS");       // file locks
    print_limit(RLIMIT_MEMLOCK, "RLIMIT_MEMLOCK");   // locked memory
    print_limit(RLIMIT_MSGQUEUE, "RLIMIT_MSGQUEUE"); // POSIX message queue bytes
    print_limit(RLIMIT_NICE, "RLIMIT_NICE");         // nice value ceiling
    print_limit(RLIMIT_NOFILE, "RLIMIT_NOFILE");     // open files
    print_limit(RLIMIT_NPROC, "RLIMIT_NPROC");       // processes per user
    print_limit(RLIMIT_RSS, "RLIMIT_RSS");           // resident set size
    print_limit(RLIMIT_RTPRIO, "RLIMIT_RTPRIO");     // real-time priority
    print_limit(RLIMIT_SIGPENDING, "RLIMIT_SIGPENDING"); // pending signals
    print_limit(RLIMIT_STACK, "RLIMIT_STACK");       // stack size

    return 0;
}
