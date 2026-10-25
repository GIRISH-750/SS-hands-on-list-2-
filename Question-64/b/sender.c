/*
 * Q64 (program 2): Send SIGSTOP to another process using kill().
 * Usage: ./sender <pid of receiver>
 *
 * After SIGSTOP the receiver stops printing (it is stopped, not
 * handling the signal). After 5 seconds we send SIGCONT so it
 * continues, which shows it was only stopped.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    if (kill(pid, SIGSTOP) == -1) {
        perror("kill SIGSTOP");
        return 1;
    }
    printf("Sent SIGSTOP to %d. It is now stopped (check: ps -o pid,stat -p %d)\n", pid, pid);

    sleep(5);

    kill(pid, SIGCONT);
    printf("Sent SIGCONT to %d. It continues running.\n", pid);

    return 0;
}
