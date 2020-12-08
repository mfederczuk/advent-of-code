# Advent of Code 2020 - Day 8 - Part 1
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

BEGIN {
	# "creating" an array with a length of zero
	instructions[0];
	delete instructions[0];
}

{
	instructions[length(instructions)] = $0;
}

END {
	visited_instruction_indices[0];
	delete visited_instruction_indices[0];

	acc = 0;

	for(instruction_i = 0; instruction_i < length(instructions); ) {
		already_visited_instruction = 0;
		for(visited_instruction_indices_i in visited_instruction_indices) {
			if(visited_instruction_indices[visited_instruction_indices_i] == instruction_i) {
				already_visited_instruction = 1;
				break;
			}
		}
		if(already_visited_instruction) break;

		instruction = instructions[instruction_i];

		visited_instruction_indices[length(visited_instruction_indices)] = instruction_i;

		if(instruction ~ /^nop/) {
			++instruction_i;
		} else if(instruction ~ /^acc [+-][0-9]+/) {
			acc += substr(instruction, 4);
			++instruction_i;
		} else if(instruction ~ /^jmp [+-][0-9]+/) {
			instruction_i += substr(instruction, 4);
		}
	}

	print(acc);
}
