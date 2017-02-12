#pragma once

#include <type_traits>
#include <numeric>

#include "type_traits.hpp"
#include "tensor_facade.hpp"
#include "tensor.hpp"

namespace sor {

	template<typename Type, std::size_t N>
	using vector = tensor<Type, N>;

	template<typename Type, std::size_t N>
	struct tensor<Type, N> : tensor_facade<Type, N> {

		/* Inherit base constructors and assignment operators.
		*/
		using tensor_facade<Type, N>::tensor_facade;
		using tensor_facade<Type, N>::operator=;

		/* Vector subscript access.
		*/
		Type& operator[](std::size_t i) noexcept { return (*this)(i); }
		Type const& operator[](std::size_t i) const noexcept { return (*this)(i); }

	};

	/* Implementation of the `sor::order` metaprogramming function.
	*/
	template<typename Type, std::size_t N>
	struct order<vector<Type, N>>
		: public std::integral_constant<std::size_t, 1> {};

	/* Implementation of the `sor::extent` metaprogramming function.
	*/
	template<typename Type, std::size_t N>
	struct extent<vector<Type, N>, 0>
		: public std::integral_constant<std::size_t, N> {};

	/* Implementation of the `std::is_tensor` metaprogramming function.
	*/
	template<typename Type, std::size_t N>
	struct is_tensor<vector<Type, N>> : std::true_type {};
	
}