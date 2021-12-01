# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -pedantic-errors

all: part1 part2
.PHONY: all

part1 part2: %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f part1 part2
