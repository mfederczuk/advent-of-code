# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

import sys

input_file = "example_input"
if len(sys.argv) >= 2:
	input_file = sys.argv[1]

with open(input_file, "r") as f:
	file = f.read()

groups = file.split("\n\n")

questions = []
for ch in range(ord("a"), ord("z") + 1):
	questions += chr(ch)

n = 0
for group in groups:
	for question in questions:
		if question in group:
			n += 1

print(n)
