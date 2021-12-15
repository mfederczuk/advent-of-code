# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS += -std=c++17 \
                     -Wall -Wextra -Wno-unknown-pragmas \
                     -pedantic -Wpedantic -pedantic-errors -Werror=pedantic


override part_sources  := $(notdir $(shell find . -maxdepth 1 -type f                    -name 'part[12].cpp' | sort))
override other_sources := $(notdir $(shell find . -maxdepth 1 -type f -name '*.cpp' -not -name 'part[12].cpp' | sort))

override headers := $(shell find . -type f -name '*.hpp') ../aoc2021.hpp

override part_targets  := $(basename $(part_sources))
override other_targets := $(basename $(other_sources))
override targets := $(part_targets) $(other_targets)


all: $(targets)
.PHONY: all

$(targets): %: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -fv part1 part2 $(other_targets)
