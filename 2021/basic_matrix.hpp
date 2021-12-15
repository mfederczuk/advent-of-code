/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_BASIC_MATRIX_HPP
#define AOC_2021_BASIC_MATRIX_HPP

#include <array>
#include <type_traits>
#include <utility>
#include <vector>

template<
	typename ElementT,
	typename RowT = std::vector<ElementT>,
	typename RowsContainerT = std::vector<RowT>
>
class basic_matrix;

template<typename ElementT, std::size_t RowsN, std::size_t ColumnsN = RowsN>
using array_matrix = basic_matrix<
	                     ElementT,
	                     std::array<ElementT, RowsN>,
	                     std::array<std::array<ElementT, ColumnsN>, RowsN>
                     >;

template<typename ElementT, typename RowT, typename RowsContainerT>
class basic_matrix {
	static_assert(std::is_same_v<ElementT, typename RowT::value_type>);
	static_assert(std::is_same_v<RowT, typename RowsContainerT::value_type>);

	public:
		using y_axis_type = typename RowsContainerT::size_type;
		using x_axis_type = typename RowT::size_type;

		using       element_type      = typename RowT::value_type;
		using       element_reference = typename RowT::reference;
		using const_element_reference = typename RowT::const_reference;

		using       row_type      = typename RowsContainerT::value_type;
		using       row_reference = typename RowsContainerT::reference;
		using const_row_reference = typename RowsContainerT::const_reference;

	private:
		RowsContainerT _rows;

	public:
		[[nodiscard]] inline basic_matrix() = default;

		[[nodiscard]] basic_matrix(const basic_matrix&  other) = default;
		[[nodiscard]] basic_matrix(      basic_matrix&& other) = default;

		[[nodiscard]] explicit inline basic_matrix(const RowsContainerT&  rows) : _rows(rows)            {}
		[[nodiscard]] explicit inline basic_matrix(      RowsContainerT&& rows) : _rows(std::move(rows)) {}

		#pragma region element access

		[[nodiscard]] inline       RowsContainerT& rows()       noexcept { return _rows; }
		[[nodiscard]] inline const RowsContainerT& rows() const noexcept { return _rows; }


		[[nodiscard]] inline       row_reference row_at(y_axis_type y)       { return _rows.at(y); }
		[[nodiscard]] inline const_row_reference row_at(y_axis_type y) const { return _rows.at(y); }

		[[nodiscard]] inline       row_reference operator[](y_axis_type y)       { return _rows[y]; }
		[[nodiscard]] inline const_row_reference operator[](y_axis_type y) const { return _rows[y]; }


		[[nodiscard]] inline       element_reference element_at(y_axis_type y, x_axis_type x)       { return _rows.at(y).at(x); }
		[[nodiscard]] inline const_element_reference element_at(y_axis_type y, x_axis_type x) const { return _rows.at(y).at(x); }

		#pragma endregion

		[[nodiscard]] inline y_axis_type rows_count (             ) const { return _rows.size();    }
		[[nodiscard]] inline x_axis_type row_size   (y_axis_type y) const { return _rows[y].size(); }

		[[nodiscard]]
		std::size_t total_elements_count() const {
			std::size_t count = 0;

			for(const_row_reference row : _rows) {
				count += row.size();
			}

			return count;
		}

		[[nodiscard]] inline y_axis_type max_y (             ) const { return (rows_count() - 1); }
		[[nodiscard]] inline x_axis_type max_x (y_axis_type y) const { return (row_size(y)  - 1); }

		[[nodiscard]] inline bool is_at_top_edge    (y_axis_type y               ) const { return (y == 0);        }
		[[nodiscard]] inline bool is_at_bottom_edge (y_axis_type y               ) const { return (y == max_y());  }
		[[nodiscard]] inline bool is_at_left_edge   (x_axis_type x               ) const { return (x == 0);        }
		[[nodiscard]] inline bool is_at_right_edge  (y_axis_type y, x_axis_type x) const { return (x == max_x(y)); }

		[[nodiscard]]
		inline bool operator==(const basic_matrix& other) const {
			return (this->_rows == other._rows);
		}
		[[nodiscard]]
		inline bool operator!=(const basic_matrix& other) const {
			return !(this->operator==(other));
		}
};

#endif /* AOC_2021_BASIC_MATRIX_HPP */
