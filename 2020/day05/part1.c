/*
 * Advent of Code 2020 - Day 5 - Part 1
 * Copyright (C) 2020  Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdio.h>

int main(int argc, char** argv) {
	char* input_file = "example_input";
	if(argc >= 2) input_file = argv[1];

	short int highest_id = -1;

	FILE* f = fopen(input_file, "r");
	char buf[10]; // 10 = (7 chars of front/back) + (3 chars of left/right)

	size_t i;
	short int min_row, max_row,
	          min_col, max_col,
	          tmp_id;

	while(fread(buf, sizeof(*buf), (sizeof(buf) / sizeof(*buf)), f) == (sizeof(buf) / sizeof(*buf))) {
		min_row = 0;
		max_row = 127;
		for(i = 0; i < 7; ++i) {
			switch(buf[i]) {
				case('F'): {
					max_row -= (max_row - (min_row - 1)) / 2;
					break;
				}
				case('B'): {
					min_row += (max_row - (min_row - 1)) / 2;
				}
			}
		}

		min_col = 0;
		max_col = 7;
		for(; i < 10; ++i) {
			switch(buf[i]) {
				case('L'): {
					max_col -= (max_col - (min_col - 1)) / 2;
					break;
				}
				case('R'): {
					min_col += (max_col - (min_col - 1)) / 2;
				}
			}
		}

		tmp_id = (min_row * 8 + min_col);
		if(tmp_id > highest_id) highest_id = tmp_id;

		fgetc(f); // skip newline
	}

	fclose(f);

	printf("%hd\n", highest_id);

	return 0;
}
