/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "../optional_reference.hpp"
#include <array>
#include <cstddef>
#include <istream>

constexpr inline const std::size_t steps = 100;

[[nodiscard]]
constexpr inline int digit_to_int(char digit) noexcept {
	return static_cast<int>(digit - '0');
}

struct octopus {
	int energy;
	bool flashed_this_step;
};

std::size_t invoke_flash_process(
	std::array<std::array<octopus, 10>, 10>& rows,
	std::size_t x,
	std::size_t y,
	bool increment
) {
	octopus& octopus = rows[y][x];

	octopus.energy += increment;

	if(octopus.energy <= 9 || octopus.flashed_this_step) {
		return 0;
	}

	std::size_t flashes = 0;

	octopus.flashed_this_step = true;
	++flashes;


	const bool at_top_edge = (y == 0);
	const bool at_bottom_edge = (y == 9);
	const bool at_left_edge = (x == 0);
	const bool at_right_edge = (x == 9);

	if(!at_top_edge) {
		// top left
		if(!at_left_edge) flashes += invoke_flash_process(rows, (x - 1), (y - 1), true);

		// top middle
		flashes += invoke_flash_process(rows, x, (y - 1), true);

		// top right
		if(!at_right_edge) flashes += invoke_flash_process(rows, (x + 1), (y - 1), true);
	}

	// center left
	if(!at_left_edge) flashes += invoke_flash_process(rows, (x - 1), y, true);

	// center right
	if(!at_right_edge) flashes += invoke_flash_process(rows, (x + 1), y, true);

	if(!at_bottom_edge) {
		// bottom left
		if(!at_left_edge) flashes += invoke_flash_process(rows, (x - 1), (y + 1), true);

		// bottom middle
		flashes += invoke_flash_process(rows, x, (y + 1), true);

		// bottom right
		if(!at_right_edge) flashes += invoke_flash_process(rows, (x + 1), (y + 1), true);
	}

	return flashes;
}

ANSWER solution(std::istream& input) {
	std::array<std::array<octopus, 10>, 10> rows;

	char ch;
	for(std::array<octopus, 10>& row : rows) {
		for(octopus& octopus : row) {
			input >> ch;
			octopus.energy = digit_to_int(ch);
		}
	}

	std::size_t total_flashes = 0;
	bool flashed;
	std::size_t new_flashes;

	for(std::size_t step = 0; step < steps; ++step) {
		for(std::array<octopus, 10>& row : rows) {
			for(octopus& octopus : row) {
				octopus.flashed_this_step = false;
				++(octopus.energy);
			}
		}

		do {
			flashed = false;

			for(std::size_t y = 0; y < rows.size(); ++y) {
				std::array<octopus, 10>& row = rows[y];

				for(std::size_t x = 0; x < row.size(); ++x) {
					new_flashes = invoke_flash_process(rows, x, y, false);
					flashed = (flashed || (new_flashes > 0));
					total_flashes += new_flashes;
				}
			}
		} while(flashed);

		for(std::array<octopus, 10>& row : rows) {
			for(octopus& octopus : row) {
				if(octopus.flashed_this_step) {
					octopus.energy = 0;
				}
			}
		}
	}

	return total_flashes;
}
