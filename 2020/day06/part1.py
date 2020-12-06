# Advent of Code 2020 - Day 6 - Part 1
# Copyright (C) 2020  Michael Federczuk
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
