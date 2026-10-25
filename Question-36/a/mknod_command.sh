#!/bin/bash
# Q36a: Create a FIFO using the mknod command.
# "p" means create a named pipe (FIFO).

mknod myfifo_mknod p

# The first character of the permissions is "p" for a FIFO
ls -l myfifo_mknod
