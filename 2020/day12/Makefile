SHELL = /bin/sh
GHC ?= ghc

all: part1 part2
.PHONY: all

part1 part2: %: %.hs
	$(GHC) -o $@ $<

clean:
	rm -f part1 part1.hi part1.o part2 part2.hi part2.o
