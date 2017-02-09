#pragma once

#include "tensor_facade.hpp"
#include "tensor.hpp"
#include "algebra.hpp"

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

}