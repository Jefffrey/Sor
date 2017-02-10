#pragma once

#include "type_traits.hpp"
#include "tensor_facade.hpp"
#include "tensor.hpp"

namespace sor {

	template<typename Type, std::size_t N, std::size_t M>
	using matrix = tensor<Type, N, M>;

	template<typename Type, std::size_t N, std::size_t M>
	struct tensor<Type, N, M> : tensor_facade<Type, N, M> {

		/* Inherit base constructors and assignment operators.
		*/
		using tensor_facade<Type, N, M>::tensor_facade;
		using tensor_facade<Type, N, M>::operator=;

	};

	/* Implementation of the `sor::order` metaprogramming function.
	*/
	template<typename Type, std::size_t N, std::size_t M>
	struct order<matrix<Type, N, M>>
		: public std::integral_constant<std::size_t, 2> {};

	/* Implementation of the `sor::extent` metaprogramming function.
	*/
	template<typename Type, std::size_t N, std::size_t M>
	struct extent<matrix<Type, N, M>, 0>
		: public std::integral_constant<std::size_t, N> {};

	template<typename Type, std::size_t N, std::size_t M>
	struct extent<matrix<Type, N, M>, 1>
		: public std::integral_constant<std::size_t, M> {};

	/* Implementation of the `std::is_tensor` metaprogramming function.
	*/
	template<typename Type, std::size_t N, std::size_t M>
	struct is_tensor<matrix<Type, N, M>> : std::true_type {};

}