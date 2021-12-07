# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CXX ?= c++

CXXFLAGS += -std=c++17 \
            -Ofast \
            -Wall -Wextra \
            -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override dollar := $

override parts := $(shell for part in part1 part2; do if [ -f $(dollar)part.cpp ]; then echo $(dollar)part; fi; done)

all: $(parts)
.PHONY: all

$(parts): %: %.cpp day06_utils.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(parts)
