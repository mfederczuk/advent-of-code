# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

BEGIN {
	# "creating" an array with a length of zero

	instructions[0];
	delete instructions[0];

	visited_instruction_indices[0];
	delete visited_instruction_indices[0];
}

{
	instructions[length(instructions)] = $0;
}

# sets `acc` to -1 when program will be stuck in an infinite loop
# `acc` will be a positive integer (or 0) otherwise
function check(changed_instructions) {
	split("", visited_instruction_indices); # clears the array

	acc = 0;

	for(instruction_i = 0; instruction_i < length(changed_instructions); ) {
		for(visited_instruction_indices_i in visited_instruction_indices) {
			if(visited_instruction_indices[visited_instruction_indices_i] == instruction_i) {
				acc = -1;
				return;
			}
		}

		instruction = changed_instructions[instruction_i];

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
}

END {
	instructions_clone_i = 0;

	do {
		for(instruction_i in instructions) {
			instructions_clone[instruction_i] = instructions[instruction_i];
		}

		# we're pretty much just changing every nop and jmp that we can find and see if it works
		# there's probably a better way to do this... yep
		#                                          i ain't attempting it tho
		for(; instructions_clone_i < length(instructions_clone) &&
		      !(instructions_clone[instructions_clone_i] ~ /^(nop|jmp [+-][0-9]+)/); ++instructions_clone_i);

		if(instructions_clone[instructions_clone_i] ~ /^nop/) {
			instructions_clone[instructions_clone_i] = "jmp" substr(instructions_clone[instructions_clone_i], 4);
		} else { # instructions_clone[instructions_clone_i] ~ /^jmp [+-][0-9]+/
			instructions_clone[instructions_clone_i] = "nop" substr(instructions_clone[instructions_clone_i], 4);
		}
		++instructions_clone_i;

		check(instructions_clone);
	} while(acc == -1);

	print(acc);
}
