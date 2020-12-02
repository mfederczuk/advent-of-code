SHELL = /bin/sh
CXX ?= c++

override CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -pedantic-errors

all: part1
.PHONY: all

part1: part1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f part1
