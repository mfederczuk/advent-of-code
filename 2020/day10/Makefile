# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
KOTLINC ?= kotlinc

all: part1.jar part2.jar
.PHONY: all

part1.jar part2.jar: %.jar: %.kt
	$(KOTLINC) $< -include-runtime -d $@

clean:
	rm -f part1.jar part2.jar
