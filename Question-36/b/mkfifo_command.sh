#!/bin/bash
# Q36b: Create a FIFO using the mkfifo command.

mkfifo myfifo_mkfifo

# The first character of the permissions is "p" for a FIFO
ls -l myfifo_mkfifo
