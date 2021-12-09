# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS += -std=c++17 \
                     -Wall -Wextra \
                     -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override parts := $(basename $(shell find . -type f -path './part[12].cpp'))
override headers := $(shell find . -type f -name '*.hpp')

all: $(parts)
.PHONY: all

$(parts): %: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -fv part1 part2
