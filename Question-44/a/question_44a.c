/*
 * Q44a: Receive a message from the queue with flag 0.
 * With flag 0, msgrcv BLOCKS until a message arrives.
 * msgtyp = 0 means "take the first message of any type".
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key = ftok("/tmp", 'Q');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msg m;

    printf("Waiting for a message (blocks if the queue is empty)...\n");

    if (msgrcv(msqid, &m, sizeof(m.mtext), 0, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received (type %ld): %s\n", m.mtype, m.mtext);

    return 0;
}
