#pragma once

#include <array>
#include <algorithm>

#include "type_traits.hpp"
#include "detail/tmp.hpp"

namespace sor {

	/* Implementation details.
	*/
	namespace detail {

		template<std::size_t... Dims, typename... Args>
		std::size_t flatten_indexes(Args... args) {

			std::initializer_list<std::size_t> indexes = { static_cast<std::size_t>(args)... };
			std::initializer_list<std::size_t> dimensions = { Dims... };

			std::size_t index = 0;
			auto last_index = indexes.end() - 1;
			for (
					auto i = indexes.begin(), d = dimensions.end() - 1; 
					i < last_index && d >= dimensions.begin(); 
					i++, d--
				) {
				index += *i;
				index *= *d;
			}
			index += *last_index;

			return index;

		}

	}

	/* The tansor class.
	*/
	template<typename Type, std::size_t... Dims>
	struct tensor_facade {

		/* Regular default, copy and move constructors work as you would expect.
		*/
		tensor_facade() = default;
		tensor_facade(tensor_facade const&) = default;
		tensor_facade(tensor_facade&&) = default;

		/* Constructor that initializes the array as if you were to initialize an array of multiple
		 * dimensions (left to right, top to bottom, front to back, etc...).
		*/
		explicit tensor_facade(std::initializer_list<Type> const& list) {
			std::copy(list.begin(), list.end(), array.begin());
		}

		/* Copy and move assignment work as you would normally expect.
		*/
		tensor_facade& operator=(tensor_facade const&) = default;
		tensor_facade& operator=(tensor_facade&&) = default;

		/* Element access operator. It access the member based on the given indexes.
		 * Example:
		 * 		sor::tensor<int, 3, 4> matrix({
		 * 			0, 1, 2, 3,
		 * 			4, 5, 6, 7,
		 * 			8, 9, 10, 11
		 * 		});
		 *		std::cout << matrix(2, 2); // = 6
		*/
		template<typename... Args>
		Type& operator()(Args... args) {
			static_assert(
				sizeof...(Args) == sizeof...(Dims), 
				"Number of indeces and order don't match"
			);
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

		template<typename... Args>
		Type const& operator()(Args... args) const {
			static_assert(
				sizeof...(Args) == sizeof...(Dims), 
				"Number of indeces and order don't match"
			);
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

	private:

		std::array<Type, detail::multiply<Dims...>::value> array;

	};

}