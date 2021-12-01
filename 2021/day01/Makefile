SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS := -std=c++17 \
                     -Wall -Wextra \
                     -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

all: part1
.PHONY: all

part1: part1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f part1
