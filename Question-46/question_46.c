/*
 * Q46: Remove the message queue using msgctl with IPC_RMID.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("/tmp", 'Q');
    int msqid = msgget(key, 0);
    if (msqid == -1) {
        perror("msgget (queue does not exist)");
        return 1;
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        return 1;
    }

    printf("Message queue %d removed. Check with 'ipcs -q'.\n", msqid);

    return 0;
}
