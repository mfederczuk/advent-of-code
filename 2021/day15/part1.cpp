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
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

struct point_size_pair_hash final {
	[[nodiscard]]
	inline std::size_t operator()(const point& p, std::size_t size) const noexcept {
		const std::size_t point_hash = std::hash<point>{}(p);
		const std::size_t size_hash = std::hash<std::size_t>{}(size);
		return point_hash ^ (size_hash << 1);
	}
};

[[nodiscard]]
std::size_t calculate_path_risk(const matrix& cave, const std::vector<point>& path) {
	if(path.empty()) {
		return std::numeric_limits<std::size_t>::max();
	}

	std::size_t total_risk = 0;

	std::for_each(
		path.cbegin() + 1,
		path.cend(),
		[&total_risk, &cave](const point& point) {
			total_risk += cave[point.y][point.x];
		}
	);

	return total_risk;
}

[[nodiscard]]
bool has_visited_point(const std::vector<point>& path, const point& point) {
	return (std::find(path.cbegin(), path.cend(), point) != path.cend());
}

void find_optimal_path(
	const matrix& cave,
	std::vector<point>& optimal_path,
	std::unordered_map<point, std::size_t>& cached_points,
	const std::vector<point>& current_path
) {
	const std::size_t max_y = cave.max_y();
	const std::size_t max_x = cave.max_x(max_y);

	const std::size_t current_path_risk = calculate_path_risk(cave, current_path);

	const point& current_point = current_path.back();


	// check if we're at the destination point
	if(current_point == point {max_x, max_y}) {
		if(current_path_risk < calculate_path_risk(cave, optimal_path)) {
			optimal_path = current_path;
		}

		return;
	}


	cached_points[current_point] = current_path_risk;


	// which next points we move towards is optimized by prediction:
	// 1. either right or down, whichever has a smaller risk level
	// 2. down or right, whichever was not chosen in the last step
	// 3. left
	// 4. up
	std::vector<point> next_points_to_consider;

	// checking right point
	if(!(cave.is_at_right_edge(current_point.y, current_point.x)) &&
	   !has_visited_point(current_path, {current_point.x + 1, current_point.y})) {

		next_points_to_consider.push_back({current_point.x + 1, current_point.y});
	}

	// checking lower point
	if(!(cave.is_at_bottom_edge(current_point.y)) &&
	   !has_visited_point(current_path, {current_point.x, current_point.y + 1})) {

		next_points_to_consider.push_back({current_point.x, current_point.y + 1});
	}

	std::sort(
		next_points_to_consider.begin(),
		next_points_to_consider.end(),
		[&cave](const point& p1, const point& p2) -> bool {
			return (cave[p1.y][p1.x] < cave[p2.y][p2.x]);
		}
	);

	// checking left point
	if(!(cave.is_at_left_edge(current_point.x)) &&
	   !has_visited_point(current_path, {current_point.x - 1, current_point.y})) {

		next_points_to_consider.push_back({current_point.x - 1, current_point.y});
	}

	// checking upper point
	if(!(cave.is_at_top_edge(current_point.y)) &&
	   !has_visited_point(current_path, {current_point.x, current_point.y - 1})) {

		next_points_to_consider.push_back({current_point.x, current_point.y - 1});
	}


	for(const point& next_point : next_points_to_consider) {
		const risk_level_t next_point_risk_level = cave[next_point.y][next_point.x];
		const std::size_t next_path_risk = (current_path_risk + next_point_risk_level);

		const std::size_t end_manhatten_distance = (max_y - next_point.y) + (max_x - next_point.x);

		if((next_path_risk >= cached_points[next_point]) ||
		   ((next_path_risk + end_manhatten_distance) >= calculate_path_risk(cave, optimal_path))) {

			// when we come in here, than we're already worse off than a different run, we can break it off now
			continue;
		}

		std::vector<point> next_path = current_path;
		next_path.push_back(next_point);

		find_optimal_path(cave, optimal_path, cached_points, next_path);
	}
}

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	matrix cave;
	input >> cave;

	std::vector<point> optimal_path;

	// when we get to a cached point, and the risk in it is lower than the current risk, then we know that from this
	// point onward, we will not be able to get the optimal path
	std::unordered_map<point, std::size_t> cached_points;
	for(std::size_t y = 0; y < cave.rows_count(); ++y) {
		for(std::size_t x = 0; x < cave.row_size(y); ++x) {
			cached_points.emplace(
				point {x, y},
				std::numeric_limits<std::size_t>::max()
			);
		}
	}

	find_optimal_path(cave, optimal_path, cached_points, {{0, 0}});

	return calculate_path_risk(cave, optimal_path);
}
