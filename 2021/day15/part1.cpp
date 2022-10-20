/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day15_utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <istream>
#include <limits>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <unistd.h>

constexpr inline std::size_t max_segment_size = 5;

struct path {
	std::vector<point> points;

	[[nodiscard]]
	bool contains_point(const point& point) const {
		return (std::find(points.cbegin(), points.cend(), point) != points.cend());
	}

	[[nodiscard]]
	std::size_t calculate_risk(const matrix& cave) const {
		std::size_t total_risk = 0;

		std::for_each(
			points.cbegin() + 1,
			points.cend(),
			[&total_risk, &cave](const point& point) {
				total_risk += cave[point.y][point.x];
			}
		);

		return total_risk;
	}
};

struct segment_point {
	::point point;
	std::vector<::point> adjacent_points;
};

struct segment {
	std::vector<segment_point> points;

	[[nodiscard]]
	std::size_t calculate_risk(const matrix& cave) const {
		return
			std::accumulate(
				points.cbegin(),
				points.cend(),
				static_cast<std::size_t>(0),
				[&cave](const std::size_t acc, const segment_point& cur) -> std::size_t {
					return (acc + cave[cur.point.y][cur.point.x]);
				}
			);
	}

	void append_points_to_path(path& path) const {
		for(const segment_point& segment_point : points) {
			path.points.push_back(segment_point.point);
		}
	}
};

void print_cave(
	const matrix& cave,
	std::size_t optimal_path_risk,
	const path& current_path,
	const segment& current_segment
) {
	std::cout << "\033[H\033[J";

	const point& current_point = current_path.points.back();

	std::cout << "\n\n\n================================================================================================================================\n\n";

	if(optimal_path_risk != 0) {
		std::cout << "optimal risk: \033[K";
		if(optimal_path_risk == std::numeric_limits<std::size_t>::max()) {
			std::cout << "\033[31m";
		} else {
			std::cout << "\033[32m";
		}
		std::cout << optimal_path_risk << "\033[0m\n"
		             "current risk: \033[K";

		const std::size_t current_path_risk = current_path.calculate_risk(cave);

		if((optimal_path_risk == std::numeric_limits<std::size_t>::max()) || current_path_risk > optimal_path_risk) {
			std::cout << "\033[33m";
		} else {
			std::cout << "\033[32m";
		}
	} else {
		std::cout << "\n"
		             "current risk: \033[K\033[33m";
	}
	std::cout << current_path.calculate_risk(cave) << "\033[0m\n\n";

	std::cout << "current point: \033[1m" << current_point << "\033[0m\n\n";

	std::cout << "\n     ";
	for(std::size_t x = 0; x <= cave.max_x(cave.max_y()); ++x) {
		std::cout << "   \033[2m" << x << "\033[0m";
	}
	std::cout << "\n\n\n";

	for(std::size_t y = 0; y < cave.rows_count(); ++y) {
		std::cout << " \033[2m" << y << "\033[0m   ";

		for(std::size_t x = 0; x < cave.row_size(y); ++x) {
			const auto prev_it = std::find(current_path.points.cbegin(), current_path.points.cend(), point {x - 1, y});
			const auto cur_it  = std::find(current_path.points.cbegin(), current_path.points.cend(), point {x, y});

			const bool in_path = (cur_it != current_path.points.cend());
			const bool in_segment =
				(std::find_if(
					 current_segment.points.cbegin(),
					 current_segment.points.cend(),
					 [x, y](const segment_point& segment_point) -> bool {
						 return (segment_point.point == point {x, y});
					 }
				 ) != current_segment.points.cend());

			const bool connection = in_path &&
			                        (prev_it != current_path.points.cend()) &&
			                        (((prev_it + 1) == cur_it) || ((prev_it - 1) == cur_it));
			const bool connection_in_segment =
				(connection &&
				 in_segment &&
				 (std::find_if(
					 current_segment.points.cbegin(),
					 current_segment.points.cend(),
					 [x, y](const segment_point& segment_point) -> bool {
						 return (segment_point.point == point {x - 1, y});
					 }
				 ) != current_segment.points.cend()));

			const bool is_current_point = (current_point == point {x, y});

			if(connection) {
				if(connection_in_segment)
					std::cout << "\033[1;34m";
				else
					std::cout << "\033[1;35m";

				std::cout << "---";
			} else {
				std::cout <<           "   ";
			}

			if(is_current_point) std::cout << "\033[1;31m";
			else
			if(in_segment) std::cout << "\033[1;34m";
			else
			if(in_path) std::cout << "\033[1;35m";

			std::cout << static_cast<short int>(cave[y][x]);

			if(connection || in_path) std::cout << "\033[0m";
		}

		std::cout << "\n     ";

		for(std::size_t x = 0; x < cave.row_size(y); ++x) {
			const auto top_it = std::find(current_path.points.cbegin(), current_path.points.cend(), point {x, y});
			const auto bot_it = std::find(current_path.points.cbegin(), current_path.points.cend(), point {x, y + 1});

			const bool connection = (top_it != current_path.points.cend()) &&
			                        (bot_it != current_path.points.cend()) &&
			                        (((top_it + 1) == bot_it) || ((bot_it + 1) == top_it));
			const bool connection_in_segment =
				(connection &&
				 (std::find_if(
					 current_segment.points.cbegin(),
					 current_segment.points.cend(),
					 [x, y](const segment_point& segment_point) -> bool {
						 return (segment_point.point == point {x, y});
					 }
				 ) != current_segment.points.cend()) &&
				 (std::find_if(
					 current_segment.points.cbegin(),
					 current_segment.points.cend(),
					 [x, y](const segment_point& segment_point) -> bool {
						 return (segment_point.point == point {x, y + 1});
					 }
				 ) != current_segment.points.cend()));

			std::cout << "   ";
			if(connection) {
				if(connection_in_segment)
					std::cout << "\033[1;34m";
				else
					std::cout << "\033[1;35m";

				std::cout << "|" "\033[0m";
			} else {
				std::cout << ' ';
			}
		}

		std::cout << '\n';
	}

	std::cout << "================================================================================================================================\n\n\n";
}

#define step_break usleep(100 * 1000)

[[nodiscard]]
bool is_end_point(const matrix& cave, const point& point) {
	const std::size_t max_y = cave.max_y();
	const std::size_t max_x = cave.max_x(max_y);

	return (point == ::point {max_x, max_y});
}

[[nodiscard]]
std::vector<point> determine_appropriate_adjacent_points(
	const matrix& cave,
	const std::size_t optimal_path_risk,
	const path& current_path,
	const point& current_point
) {
	if(is_end_point(cave, current_point)) {
		return {};
	}

	// which next points we move towards is optimized by prediction:
	// 1. either right or down, whichever has a smaller risk level
	// 2. down or right, whichever was not chosen in the last step
	// 3. left
	// 4. up
	std::vector<point> adjacent_points;

	// checking right point
	if(!(cave.is_at_right_edge(current_point.y, current_point.x))) {
		adjacent_points.push_back({current_point.x + 1, current_point.y});
	}

	// checking lower point
	if(!(cave.is_at_bottom_edge(current_point.y))) {
		adjacent_points.push_back({current_point.x, current_point.y + 1});
	}

	std::sort(
		adjacent_points.begin(),
		adjacent_points.end(),
		[&cave](const point& p1, const point& p2) -> bool {
			return (cave[p1.y][p1.x] < cave[p2.y][p2.x]);
		}
	);

	// checking left point
	if(!(cave.is_at_left_edge(current_point.x))) {
		adjacent_points.push_back({current_point.x - 1, current_point.y});
	}

	// checking upper point
	if(!(cave.is_at_top_edge(current_point.y))) {
		adjacent_points.push_back({current_point.x, current_point.y - 1});
	}

	const std::vector<point>::const_iterator removed_begin =
		std::remove_if(
			adjacent_points.begin(),
			adjacent_points.end(),
			[&current_path, &cave, optimal_path_risk](const point& adjacent_point) -> bool {
				if(current_path.contains_point(adjacent_point)) {
					return true;
				}

				const std::size_t current_path_risk = current_path.calculate_risk(cave);
				const std::size_t next_path_risk = (current_path_risk + cave[adjacent_point.y][adjacent_point.x]);

				const std::size_t point_end_manahatten_distance = (cave.max_y()             - adjacent_point.y) +
				                                                  (cave.max_x(cave.max_y()) - adjacent_point.x);

				return ((next_path_risk + point_end_manahatten_distance) >= optimal_path_risk);
			}
		);

	adjacent_points.erase(removed_begin, adjacent_points.cend());

	return adjacent_points;
}

[[nodiscard]]
segment create_segment(
	const matrix& cave,
	const std::size_t optimal_path_risk,
	path current_path,
	const point& starting_point
) {
	segment segment;

	point current_point = starting_point;

	for(std::size_t n = 0; n < max_segment_size; ++n) {
		segment.points.push_back({
			current_point,
			std::move(determine_appropriate_adjacent_points(cave, optimal_path_risk, current_path, current_point))
		});

		current_path.points.push_back(current_point);

		// print_cave(cave, optimal_path_risk, current_path, segment);
		// step_break;

		if(segment.points.back().adjacent_points.empty()) {
			break;
		}

		current_point = segment.points.back().adjacent_points.front();
	}
	// step_break;

	return segment;
}

void start_segments(
	const matrix& cave,
	path& optimal_path,
	std::size_t& optimal_path_risk,
	path current_path
) {
	const point& current_point = current_path.points.back();

	print_cave(cave, optimal_path_risk, current_path, {});
	step_break;

	const std::vector<point> appropriate_adjacent_points =
		determine_appropriate_adjacent_points(
			cave,
			optimal_path_risk,
			current_path,
			current_point
		);

	std::vector<segment> next_segments;
	for(const point& adjacent_point : appropriate_adjacent_points) {
		next_segments.push_back(std::move(create_segment(cave, optimal_path_risk, current_path, adjacent_point)));
	}

	std::stable_sort(
		next_segments.begin(),
		next_segments.end(),
		[&cave](const segment& s1, const segment& s2) -> bool {
			return (s1.calculate_risk(cave) < s2.calculate_risk(cave));
		}
	);

	for(const segment& next_segment : next_segments) {
		path next_path = current_path;
		next_segment.append_points_to_path(next_path);

		decltype(next_segment.points)::const_reverse_iterator it = next_segment.points.crbegin();

		if(is_end_point(cave, next_path.points.back())) {
			const std::size_t next_path_risk = next_path.calculate_risk(cave);
			if(next_path_risk < optimal_path_risk) {
				optimal_path = next_path;
				optimal_path_risk = next_path_risk;
			}

			++it;
			next_path.points.pop_back();
		}

		for(; it != next_segment.points.crend(); ++it) {
			start_segments(cave, optimal_path, optimal_path_risk, next_path);
			// step_break;
			next_path.points.pop_back();
		}
	}
}

[[nodiscard]]
std::size_t find_optimal_path_risk(const matrix& cave) {
	path optimal_path;
	std::size_t optimal_path_risk = std::numeric_limits<std::size_t>::max();

	std::cout << "\033[?1049h";

	start_segments(cave, optimal_path, optimal_path_risk, /* current path: */ path {std::vector {point {0, 0}}});

	std::cout << "\033[?1049l";

	return optimal_path_risk;
}

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	matrix cave;
	input >> cave;

	return find_optimal_path_risk(cave);
}
