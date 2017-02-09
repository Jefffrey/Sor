#pragma once

#include "tensor_facade.hpp"
#include "tensor.hpp"
#include "algebra.hpp"

namespace sor {

	template<typename Type, std::size_t N, std::size_t M>
	using matrix = tensor<Type, N, M>;

	template<typename Type, std::size_t N, std::size_t M>
	struct tensor<Type, N, M> : tensor_facade<Type, N, M> {

		/* Inherit base constructors.
		*/
		using tensor_facade<Type, N, M>::tensor_facade;

	};

}