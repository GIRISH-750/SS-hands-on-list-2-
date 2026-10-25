/*
 * Q44b: Receive a message from the queue with IPC_NOWAIT.
 * If the queue is empty, msgrcv returns -1 immediately
 * with errno = ENOMSG instead of blocking.
 */
#include <stdio.h>
#include <errno.h>
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

    if (msgrcv(msqid, &m, sizeof(m.mtext), 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message in the queue (IPC_NOWAIT returned immediately)\n");
        } else {
            perror("msgrcv");
        }
        return 1;
    }

    printf("Received (type %ld): %s\n", m.mtype, m.mtext);

    return 0;
}
