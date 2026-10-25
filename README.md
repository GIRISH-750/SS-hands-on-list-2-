# SS Hands-on List 2

Solutions to the System Software hands-on list 2 (Questions 31–64), written in C.

Each question has its own `Question-N` folder. Multi-part questions have `a/`, `b/`, ... subfolders.

## Compile

```
gcc question_N.c -o question_N
```

Programs that use threads (Q52b, Q58) need `-pthread`:

```
gcc question_58.c -o question_58 -pthread
```

## Questions

| Q | Topic |
|---|-------|
| 31 | Create a pipe, write to it and read from it |
| 32 | Send data from parent to child |
| 33 | Two-way communication between parent and child |
| 34 | `ls -l \| wc` using (a) dup, (b) dup2, (c) fcntl |
| 35 | Count directories with `ls -l \| grep ^d \| wc` using dup2 |
| 36 | Create a FIFO: (a) mknod command, (b) mkfifo command, (c) strace comparison, (d) mknod system call, (e) mkfifo function |
| 37 | FIFO one-way communication |
| 38 | FIFO two-way communication |
| 39 | Wait up to 10 seconds for FIFO data using select |
| 40 | Max open files per process and pipe size |
| 41 | Create a message queue, print key and ID |
| 42 | Message queue info using msqid_ds and ipc_perm |
| 43 | Send messages to the message queue |
| 44 | Receive messages with (a) flag 0, (b) IPC_NOWAIT |
| 45 | Change message queue permissions |
| 46 | Remove the message queue |
| 47 | Shared memory: write, read-only attach, detach, remove |
| 48 | Create (a) a binary and (b) a counting semaphore |
| 49 | Semaphores: (a) ticket number, (b) protect shared memory, (c) two resources with a counting semaphore, (d) remove semaphores |
| 50 | Deadlock using semaphores |
| 51 | Socket communication between two machines |
| 52 | Concurrent server using (a) fork, (b) pthread_create |
| 53 | Interval timer (10 s + 10 µs) with (a) ITIMER_REAL, (b) ITIMER_VIRTUAL, (c) ITIMER_PROF |
| 54 | Print resource limits with getrlimit |
| 55 | Set a resource limit with setrlimit |
| 56 | Time 100 getppid() calls using the time stamp counter |
| 57 | System limits using sysconf |
| 58 | Create three threads and print their IDs |
| 59 | Catch signals with signal(): SIGSEGV, SIGINT, SIGFPE, SIGALRM (alarm and setitimer), SIGVTALRM, SIGPROF |
| 60 | Ignore SIGINT, then reset to default, using signal() |
| 61 | Catch SIGSEGV, SIGINT, SIGFPE using sigaction() |
| 62 | Ignore SIGINT, then reset to default, using sigaction() |
| 63 | Create an orphan process (child kills parent with SIGKILL) |
| 64 | Try to catch SIGSTOP sent with kill() |

## Programs that need two terminals

| Q | Terminal 1 | Terminal 2 |
|---|------------|------------|
| 37 | `b/reader` | `a/writer` |
| 38 | `a/program1` | `b/program2` |
| 39 | `a/question_39` (waits 10 s) | `b/writer` |
| 51 | `a/server` | `b/client <server-ip>` (use `127.0.0.1` on one machine) |
| 52 | `a/question_52a` or `b/question_52b` | `client/client 8081` (fork) or `client/client 8082` (threads); open several clients |
| 64 | `a/receiver` (prints its PID) | `b/sender <PID>` |

Q49a, Q49b and Q49c are best shown by running the same program in two or three terminals at once: the later ones wait until the first one leaves the critical section.

## Notes

- **Message queues (Q41–Q46)** all use the key `ftok("/tmp", 'Q')`, so they work on the same queue. Run Q41 first and Q46 last. Check with `ipcs -q`.
- **Q36c result:** `mknod` and `mkfifo` make the same system call (`mknodat(..., S_IFIFO|0666)`) and the same number of system calls, so neither is meaningfully more efficient.
- **Q50** deadlocks on purpose and waits forever. Press Ctrl+C to stop it; it removes its semaphores before exiting.
- **Q53 b/c and Q59 f/g** use CPU-time timers, so they busy-loop on purpose (100% CPU) until the timer fires.
- **Q56** uses the `rdtsc` instruction, so it works on x86 / x86_64 CPUs.
- **Q64:** SIGSTOP can't be caught, blocked or ignored. `signal()` fails with "Invalid argument", and the process is just stopped (state `T` in `ps`).
