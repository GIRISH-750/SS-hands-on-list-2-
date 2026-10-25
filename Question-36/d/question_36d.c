/*
 * Q36d: Create a FIFO using the mknod system call.
 * S_IFIFO tells mknod to create a FIFO; the last argument (dev)
 * is only used for device files, so it is 0 here.
 */
#include <stdio.h>
#include <sys/stat.h>

int main() {
    if (mknod("myfifo_d", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO 'myfifo_d' created using mknod system call\n");

    return 0;
}
