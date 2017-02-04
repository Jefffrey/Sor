#pragma once

#include <type_traits>

namespace sor {

	namespace detail {

		/*	Metaprogramming function that calculates the multiplication of all integers
		 * 	passed to it.
		 * 	Example:
		 * 		std::cout << multiply<2, 3, 4>::value;
		 *		// = 2 * 3 * 4 = 24;
		*/
		template<std::size_t N, std::size_t... Ms>
		struct multiply 
			: public std::integral_constant<std::size_t, N * multiply<Ms...>::value> {};

		template<std::size_t N>
		struct multiply<N> 
			: public std::integral_constant<std::size_t, N> {};

	}

}