#!/bin/bash
# Q36c: Use strace to see which command (mknod or mkfifo) is more efficient.
#
# strace -c prints a summary: how many system calls each command made.
# strace (without -c) shows each call, so we grep for the call that
# actually creates the FIFO.

rm -f fifo1 fifo2

echo "===== mknod: summary ====="
strace -c mknod fifo1 p 2>&1 | tail -3

echo "===== mkfifo: summary ====="
strace -c mkfifo fifo2 2>&1 | tail -3

rm -f fifo1 fifo2

echo "===== system call that creates the FIFO ====="
strace mknod fifo1 p 2>&1 | grep "^mknod"
strace mkfifo fifo2 2>&1 | grep "^mknod"

rm -f fifo1 fifo2

# Result we got (Linux):
#   Both commands make the SAME system call:
#       mknodat(AT_FDCWD, "fifoX", S_IFIFO|0666) = 0
#   and the same total number of system calls (67 each).
#
# Conclusion:
#   There is no real difference. mkfifo is just a simpler front end;
#   inside, both use mknod(at) with S_IFIFO. The extra calls in both
#   are only program startup (loading libc, locale files, etc.).
#   The exact counts can differ a little between systems.
