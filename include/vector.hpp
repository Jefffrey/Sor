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

		/* Vector addition.
		*/
		template<typename OtherType>
		auto& operator+=(vector<OtherType, N> const& rhs) {
			auto l = this->begin();
			auto r = rhs.begin();
			for (; l < this->end() && r < rhs.end(); ++l, ++r) {
				*l += *r;
			}
			return (*this);
		}

		/* Vector subtraction.
		*/
		template<typename OtherType>
		auto& operator-=(vector<OtherType, N> const& rhs) {
			auto l = this->begin();
			auto r = rhs.begin();
			for (; l < this->end() && r < rhs.end(); ++l, ++r) {
				*l -= *r;
			}
			return (*this);
		}

		/* Vector scalar product
		*/
		template<typename OtherType>
		auto& operator*=(OtherType const& rhs) {
			for (auto& i : (*this)) {
				i *= rhs;
			}
			return (*this);
		}

		/* Vector scalar division
		*/
		template<typename OtherType>
		auto& operator/=(OtherType const& rhs) {
			for (auto& i : (*this)) {
				i /= rhs;
			}
			return (*this);
		}

	};
	
}