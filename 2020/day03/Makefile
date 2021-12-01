# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
JAVAC ?= javac

all: Part1.class Part2.class
.PHONY: all

Part1.class Part2.class: %.class: %.java
	$(JAVAC) $<

clean:
	rm -f Part1.class Part2.class
