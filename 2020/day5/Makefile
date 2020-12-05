SHELL = /bin/sh
CC ?= cc

override CFLAGS := -std=c11 -Wall -Wextra -pedantic -pedantic-errors

all: part1
.PHONY: all

part1: part1.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f part1
