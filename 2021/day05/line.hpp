/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY05_LINE_HPP
#define AOC_2021_DAY05_LINE_HPP

#include "point.hpp"
#include <istream>
#include <ostream>
#include <utility>

struct line {
	class custom_iterator {
		private:
			struct line_direction {
				enum class axis_direction {
					positive,
					negative,
					undetermined
				};

				axis_direction x;
				axis_direction y;

				[[nodiscard]]
				static constexpr line_direction determine_from_two_points(const point& begin, const point& end) noexcept {
					axis_direction x = axis_direction::undetermined;

					if(begin.x < end.x) {
						x = axis_direction::positive;
					} else if(begin.x > end.x) {
						x = axis_direction::negative;
					}

					axis_direction y = axis_direction::undetermined;

					if(begin.y < end.y) {
						y = axis_direction::positive;
					} else if(begin.y > end.y) {
						y = axis_direction::negative;
					}

					return line_direction { x, y };
				}
			};

			static constexpr void increment_point(point& p, line_direction dir) noexcept {
				switch(dir.x) {
					case(line_direction::axis_direction::positive): {
						++(p.x);
						break;
					}
					case(line_direction::axis_direction::negative): {
						--(p.x);
						break;
					}
					case(line_direction::axis_direction::undetermined): ;
				}

				switch(dir.y) {
					case(line_direction::axis_direction::positive): {
						++(p.y);
						break;
					}
					case(line_direction::axis_direction::negative): {
						--(p.y);
						break;
					}
					case(line_direction::axis_direction::undetermined): ;
				}
			}
			[[nodiscard]]
			static constexpr point incremented_point(const point& p, line_direction dir) noexcept {
				point copy = p;
				increment_point(copy, dir);
				return copy;
			}

			point current;
			point past_end;

		public:
			[[nodiscard]]
			constexpr custom_iterator(point begin, point end) noexcept
					: current(begin),
					  past_end(incremented_point(end, line_direction::determine_from_two_points(begin, end))) {
			}

		private:
			[[nodiscard]]
			constexpr line_direction determine_direction() const noexcept {
				return line_direction::determine_from_two_points(current, past_end);
			}

		public:
			[[nodiscard]]
			constexpr bool has_next() const noexcept {
				return (current != past_end);
			}

			[[nodiscard]]
			constexpr const point& operator*() const noexcept {
				return current;
			}

			[[nodiscard]]
			constexpr const point* operator->() const noexcept {
				return &current;
			}

			constexpr custom_iterator& operator++() noexcept {
				increment_point(current, determine_direction());
				return *this;
			}
	};

	point begin;
	point end;

	[[nodiscard]]
	constexpr bool operator==(const line& other) const noexcept {
		return (this->begin == other.begin && this->end == other.end);
	}

	[[nodiscard]]
	constexpr bool operator!=(const line& other) const noexcept {
		return (this->begin != other.begin || this->end != other.end);
	}

	[[nodiscard]]
	constexpr custom_iterator get_iterator() const noexcept {
		return custom_iterator { begin, end };
	}

	friend std::istream& operator>>(std::istream& stream, line& line) {
		stream >> line.begin;
		stream.ignore(4); // skip " -> "
		stream >> line.end;
		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const line& line) {
		return (stream << line.begin << " -> " << line.end);
	}
};

#endif /* AOC_2021_DAY05_LINE_HPP */
