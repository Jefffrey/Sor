#pragma once

#include "tensor_facade.hpp"
#include "tensor.hpp"

namespace sor {

	template<typename Type, std::size_t N, std::size_t M>
	using matrix = tensor<Type, N, M>;

	template<typename Type, std::size_t N, std::size_t M>
	struct tensor<Type, N, M> : tensor_facade<Type, N, M> {

		/* Inherit base constructors.
		*/
		using tensor_facade<Type, N, M>::tensor_facade;

		/* Matrix addition.
		*/
		template<typename OtherType>
		auto& operator+=(matrix<OtherType, N, M> const& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				for (std::size_t j = 0; j < M; j++) {
					(*this)(i, j) += rhs(i, j);
				}
			}
			return (*this);
		}

	};

}