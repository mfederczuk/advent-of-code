SHELL = /bin/sh
JAVAC ?= javac

all: Part1.class Part2.class
.PHONY: all

Part1.class Part2.class: %.class: %.java
	$(JAVAC) $<

clean:
	rm -f Part1.class Part2.class
