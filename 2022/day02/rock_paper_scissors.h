/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY02_ROCK_PAPER_SCISSORS_H
#define YEAR2022_DAY02_ROCK_PAPER_SCISSORS_H

#include <stddef.h>

typedef size_t rps_score_t;
#define PRIrpsscore "zu"

enum rps_throw {
	ROCK,
	PAPER,
	SCISSORS,
};

enum rps_1v1_round_outcome {
	WIN,
	DRAW,
	LOOSE,
};

static inline enum rps_1v1_round_outcome rps_determine_1v1_round_outcome(const enum rps_throw player_throw,
                                                                         const enum rps_throw opponent_throw) {
	if (player_throw == opponent_throw) {
		return DRAW;
	}

	if (((player_throw + 1) % 3) == opponent_throw) {
		return LOOSE;
	}

	return WIN;
}

static inline enum rps_throw rps_determine_1v1_round_player_throw(const enum rps_throw opponent_throw,
                                                                  const enum rps_1v1_round_outcome outcome) {
	if (outcome == DRAW) {
		return opponent_throw;
	}

	if (outcome == LOOSE) {
		return (enum rps_throw)((opponent_throw + 2) % 3);
	}

	return (enum rps_throw)((opponent_throw + 1) % 3);
}

static inline rps_score_t rps_calc_1v1_round_player_score(const enum rps_throw player_throw,
                                                          const enum rps_1v1_round_outcome outcome) {
	rps_score_t throw_score;
	switch (player_throw) {
		case ROCK:     { throw_score = 1; break; }
		case PAPER:    { throw_score = 2; break; }
		case SCISSORS: { throw_score = 3; break; }
	}

	rps_score_t outcome_score;
	switch (outcome) {
		case WIN:   { outcome_score = 6; break; }
		case DRAW:  { outcome_score = 3; break; }
		case LOOSE: { outcome_score = 0; break; }
	}

	return (throw_score + outcome_score);
}

#endif /* YEAR2022_DAY02_ROCK_PAPER_SCISSORS_H */
