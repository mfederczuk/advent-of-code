# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CC ?= cc

override CFLAGS := -std=c11 -Wall -Wextra -pedantic -pedantic-errors

all: part1 part2
.PHONY: all

part1 part2: %: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f part1 part2
