CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror
keyfilter: keyfilter.c
    $(CC) $(CFLAGS) keyfilter.c -o keyfilter