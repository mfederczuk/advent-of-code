# Copyright (c) 2022 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh

CC ?= cc
CFLAGS = -std=c11 \
         -Wall -Wextra -Wconversion \
         -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override headers != find . -mindepth 1 -type f -name '*.h'

.SUFFIXES:

all: part1 part2
.PHONY: all

part1 part2: %: $(headers) %.c
	$(strip $(CC) $(CFLAGS) $(lastword $^) -o $@)

clean:
	rm -f part2 part1
.PHONY: clean
