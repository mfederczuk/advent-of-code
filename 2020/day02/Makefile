SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -pedantic-errors

all: part1 part2
.PHONY: all

part1 part2: %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f part1 part2
