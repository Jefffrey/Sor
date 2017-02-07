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
			auto l = this->begin();
			auto r = rhs.begin();
			for (; l < this->end() && r < rhs.end(); ++l, ++r) {
				*l += *r;
			}
			return (*this);
		}

		/* Matrix subtraction.
		*/
		template<typename OtherType>
		auto& operator-=(matrix<OtherType, N, M> const& rhs) {
			auto l = this->begin();
			auto r = rhs.begin();
			for (; l < this->end() && r < rhs.end(); ++l, ++r) {
				*l -= *r;
			}
			return (*this);
		}

	};

}