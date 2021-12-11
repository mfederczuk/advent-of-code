/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_OPTIONAL_REFERENCE_HPP
#define AOC_2021_OPTIONAL_REFERENCE_HPP

constexpr inline const struct nullref_t final {} nullref;

template<typename T>
class optional_reference final {
	private:
		T* ptr;

	public:
		[[nodiscard]]
		inline optional_reference(T& value) noexcept : ptr(&value) {}

		[[nodiscard]]
		constexpr inline optional_reference(nullref_t = nullref) noexcept : ptr(nullptr) {}


		inline optional_reference& operator=(T& value) noexcept {
			this->ptr = &value;
			return *this;
		}

		inline optional_reference& operator=(nullref_t) noexcept {
			this->reset();
			return *this;
		}


		[[nodiscard]]
		constexpr inline bool has_value() const noexcept {
			return (ptr != nullptr);
		}


		[[nodiscard]] inline       T& get()       noexcept { return *ptr; }
		[[nodiscard]] inline const T& get() const noexcept { return *ptr; }

		[[nodiscard]] inline       T& operator*()       noexcept { return get(); }
		[[nodiscard]] inline const T& operator*() const noexcept { return get(); }

		[[nodiscard]] inline       T* operator->()       noexcept { return ptr; }
		[[nodiscard]] inline const T* operator->() const noexcept { return ptr; }


		constexpr inline void reset() noexcept {
			ptr = nullptr;
		}
};

#endif /* AOC_2021_OPTIONAL_REFERENCE_HPP */
