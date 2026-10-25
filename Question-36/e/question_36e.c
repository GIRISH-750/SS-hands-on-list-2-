/*
 * Q36e: Create a FIFO using the mkfifo library function.
 */
#include <stdio.h>
#include <sys/stat.h>

int main() {
    if (mkfifo("myfifo_e", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO 'myfifo_e' created using mkfifo library function\n");

    return 0;
}
