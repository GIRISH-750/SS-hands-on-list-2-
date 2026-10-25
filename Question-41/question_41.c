/*
 * Q41: Create a message queue and print its key and ID.
 *
 * ftok() turns an existing path + a character into a key.
 * All message queue programs (Q41-Q46) use the same path and
 * character, so they all work on the same queue.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("/tmp", 'Q');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Key: %d (0x%x)\n", key, key);
    printf("Message queue ID: %d\n", msqid);

    return 0;
}
