#pragma once

#include "tensor_facade.hpp"
#include "tensor.hpp"

namespace sor {

	template<typename Type, std::size_t N>
	using vector = tensor<Type, N>;

	template<typename Type, std::size_t N>
	struct tensor<Type, N> : tensor_facade<Type, N> {

		/* Inherit base constructors.
		*/
		using tensor_facade<Type, N>::tensor_facade;

		/* Vector subscript access.
		*/
		Type& operator[](std::size_t i) { return (*this)(i); }
		Type const& operator[](std::size_t i) const { return (*this)(i); }

		/* Vector Addition.
		*/
		template<typename OtherType>
		auto& operator+=(vector<OtherType, N> const& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				(*this)[i] += rhs[i];
			}
			return (*this);
		}

	};
	
}