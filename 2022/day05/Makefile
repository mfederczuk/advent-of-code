#!/usr/bin/make -f

# Copyright (c) 2022 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh

CC ?= cc
CFLAGS = -std=c11 \
         -Wall -Wextra -Wconversion \
         -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override headers != find . -mindepth 1 -type f -name '*.h'

override sources != find . -mindepth 1 -maxdepth 1 -type f -name 'part[12].c'
override targets := $(sources:%.c=%)

.SUFFIXES:

all: $(targets)
.PHONY: all

$(targets): %: $(headers) %.c
	$(strip $(CC) $(CFLAGS) $(lastword $^) -o $@)

clean:
	rm -f $(targets)
.PHONY: clean
