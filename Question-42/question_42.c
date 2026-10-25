/*
 * Q42: Print information about a message queue using
 * the msqid_ds and ipc_perm structures (msgctl with IPC_STAT).
 */
#include <stdio.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("/tmp", 'Q');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msqid_ds info;
    if (msgctl(msqid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        return 1;
    }

    // ipc_perm is inside msqid_ds as info.msg_perm
    printf("a. Access permission: %o\n", info.msg_perm.mode & 0777);
    printf("b. UID: %d, GID: %d\n", info.msg_perm.uid, info.msg_perm.gid);

    // ctime() prints "Thu Jan  1 00:00:00 1970" when the time is 0 (never happened)
    printf("c. Time of last message sent: %s", ctime(&info.msg_stime));
    printf("   Time of last message received: %s", ctime(&info.msg_rtime));
    printf("d. Time of last change: %s", ctime(&info.msg_ctime));

    // __msg_cbytes is the Linux name for the current number of bytes in the queue
    printf("e. Size of the queue (bytes used): %lu\n", info.__msg_cbytes);
    printf("f. Number of messages in the queue: %lu\n", info.msg_qnum);
    printf("g. Maximum number of bytes allowed: %lu\n", info.msg_qbytes);
    printf("h. PID of last msgsnd: %d\n", info.msg_lspid);
    printf("   PID of last msgrcv: %d\n", info.msg_lrpid);

    return 0;
}
