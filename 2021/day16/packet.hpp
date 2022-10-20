/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY16_PACKET_HPP
#define AOC_2021_DAY16_PACKET_HPP

#include <cstdint>
#include <vector>

namespace aoc::day16 {


	/*
	struct literal_packet_data final {
		static constexpr const std::uint8_t group_a_mask = 0b11110000;
		static constexpr const std::uint8_t group_b_mask = 0b00001111;

		static constexpr const std::uint8_t group_a_shift = 4;

		static constexpr const std::uint8_t group_prefix_mask = 0b1000;
		static constexpr const std::uint8_t group_prefix_last = 0b1000;

		static constexpr const std::uint8_t group_data_mask   = 0b0111;


		std::vector<std::uint8_t> bytes;

		template<typename IntT = std::uintmax_t>
		[[nodiscard]]
		IntT value() const {
			std::vector<std::uint8_t> groups;
			groups.reserve(bytes.size() * 2);

			std::uint8_t group_a,
			             group_b;

			for(const std::uint8_t byte : bytes) {
				group_a = (byte & group_a_mask) >> group_a_shift;
				group_b = (byte & group_b_mask);

				groups.push_back(group_a);
				groups.push_back(group_b);
			}

			IntT sum = static_cast<IntT>(0);

			for(const std::uint8_t group : groups) {
				if((group & group_prefix_mask) == group_prefix_last) {
					break;
				}
			}

			return sum;
		}

		friend std::istream& operator>>(std::istream& stream, literal_packet_data& data) {
		}
	};

	struct operator_packet_data final {
	};

	struct packet final {
		std::uint_least8_t version : 3;
		std::uint_least8_t type : 3;

		union {
			literal_packet_data literal_data;
			operator_packet_data operator_data;
		} data;
	};
	*/
}

#endif /* AOC_2021_DAY16_PACKET_HPP */
