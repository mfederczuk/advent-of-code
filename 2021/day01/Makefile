# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS := -std=c++17 \
                     -Wall -Wextra \
                     -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override parts := part1 part2

all: $(parts)
.PHONY: all

$(parts): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(parts)
