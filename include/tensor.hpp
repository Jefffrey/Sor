#pragma once

#include <type_traits>

#include "type_traits.hpp"
#include "tensor_facade.hpp"

namespace sor {

	template<typename Type, std::size_t... Dims>
	struct tensor : tensor_facade<Type, Dims...> {

		/* Inherit base constructors.
		*/
		using tensor_facade<Type, Dims...>::tensor_facade;

	};

	/* Implementation of the `sor::order` metaprogramming function.
	*/
	template<typename Type, std::size_t... Dims>
	struct order<tensor<Type, Dims...>>
		: public std::integral_constant<std::size_t, sizeof...(Dims)> {};

	/* Implementation of the `sor::extent` metaprogramming function.
	*/
	template<typename Type, std::size_t First, std::size_t... Dims, std::size_t Index>
	struct extent<tensor<Type, First, Dims...>, Index>
		: public std::integral_constant<std::size_t, 
			extent<tensor<Type, Dims...>, Index - 1>::value
		> {};

	template<typename Type, std::size_t First, std::size_t... Dims>
	struct extent<tensor<Type, First, Dims...>, 0>
		: public std::integral_constant<std::size_t, First> {};

}