SHELL = /bin/sh
GHC ?= ghc

all: part1
.PHONY: all

part1: part1.hs
	$(GHC) -o $@ $<

clean:
	rm -f part1 part1.hi part1.o
