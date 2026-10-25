/*
 * Q45: Change the permissions of an existing message queue
 * using the msqid_ds structure:
 *   IPC_STAT -> read current settings
 *   change msg_perm.mode
 *   IPC_SET  -> write them back
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("/tmp", 'Q');
    int msqid = msgget(key, 0);   // 0 = queue must already exist
    if (msqid == -1) {
        perror("msgget (run Q41 first)");
        return 1;
    }

    struct msqid_ds info;
    if (msgctl(msqid, IPC_STAT, &info) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    printf("Old permissions: %o\n", info.msg_perm.mode & 0777);

    unsigned int newmode;
    printf("Enter new permissions in octal (e.g. 600): ");
    scanf("%o", &newmode);

    info.msg_perm.mode = newmode;

    if (msgctl(msqid, IPC_SET, &info) == -1) {
        perror("msgctl IPC_SET");
        return 1;
    }

    msgctl(msqid, IPC_STAT, &info);
    printf("New permissions: %o\n", info.msg_perm.mode & 0777);

    return 0;
}
