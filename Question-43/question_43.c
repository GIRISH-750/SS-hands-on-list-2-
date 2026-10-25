/*
 * Q43: Send messages to the message queue.
 * Check the result with:  ipcs -q
 */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long mtype;          // must be > 0
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

    printf("Enter message type (number > 0): ");
    scanf("%ld", &m.mtype);
    getchar();   // remove the newline left by scanf

    printf("Enter message text: ");
    fgets(m.mtext, sizeof(m.mtext), stdin);
    m.mtext[strcspn(m.mtext, "\n")] = '\0';

    // Size passed to msgsnd is only the text part, not mtype
    if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent. Run 'ipcs -q' to see it in the queue.\n");

    return 0;
}
