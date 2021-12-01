# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

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
