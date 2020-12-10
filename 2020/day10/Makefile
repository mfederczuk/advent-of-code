SHELL = /bin/sh
KOTLINC ?= kotlinc

all: part1.jar
.PHONY: all

part1.jar: part1.kt
	$(KOTLINC) $< -include-runtime -d $@

clean:
	rm -f part1.jar
