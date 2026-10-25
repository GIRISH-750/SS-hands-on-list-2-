/*
 * Q56: Measure the time taken by 100 getppid() calls using the
 * time stamp counter (TSC). rdtsc reads the CPU's cycle counter.
 * Works on x86 / x86_64 CPUs.
 */
#include <stdio.h>
#include <unistd.h>

static inline unsigned long long rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start = rdtsc();

    for (int i = 0; i < 100; i++) {
        getppid();
    }

    unsigned long long end = rdtsc();

    printf("Cycles for 100 getppid() calls: %llu\n", end - start);
    printf("Average cycles per call: %llu\n", (end - start) / 100);

    return 0;
}
