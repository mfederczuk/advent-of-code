/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "dynamic_sso_string.h"
#include "file_line_iter.h"
#include "rock_paper_scissors.h"
#include "string_view.h"
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char* const* const argv) {
	if (argc < 2) {
		fprintf(stderr, "%s: missing argument: <input_file>\n", argv[0]);
		return 3;
	}

	struct file_line_iter iter;
	if (file_line_iter_init(&iter, argv[1]) != 0) {
		perror("file_line_iter_init");
		return EXIT_FAILURE;
	}

	rps_score_t total_score = 0;

	struct file_line_iter_next next_line;
	do {
		if (file_line_iter_next(&iter, &next_line) != 0) {
			file_line_iter_destroy(&iter);
			return EXIT_FAILURE;
		}

		if (!(next_line.valid)) {
			break;
		}

		const struct string_view line = dynamic_sso_string_as_string_view(&(next_line.line));

		const size_t line_len = string_view_length(line);
		if (line_len > 0) {
			if (line_len != 3) {
				return EXIT_FAILURE;
			}

			enum rps_throw opponent_throw;
			switch (line.begin[0]) {
				case 'A': { opponent_throw = ROCK;     break; }
				case 'B': { opponent_throw = PAPER;    break; }
				case 'C': { opponent_throw = SCISSORS; break; }
				default: return EXIT_FAILURE;
			}

			enum rps_throw player_throw;
			switch (line.begin[2]) {
				case 'X': { player_throw = ROCK;     break; }
				case 'Y': { player_throw = PAPER;    break; }
				case 'Z': { player_throw = SCISSORS; break; }
				default: return EXIT_FAILURE;
			}

			const enum rps_1v1_round_outcome outcome = rps_determine_1v1_round_outcome(player_throw, opponent_throw);
			total_score += rps_calc_1v1_round_player_score(player_throw, outcome);
		}

		dynamic_sso_string_destroy(&(next_line.line));
	} while (1);

	printf("%" PRIrpsscore "\n", total_score);

	file_line_iter_destroy(&iter);

	return EXIT_SUCCESS;
}
