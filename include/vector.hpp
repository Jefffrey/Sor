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

		/* Vector sum.
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

		/* Vector scalar product.
		*/
		template<typename OtherType>
		auto& operator*=(OtherType const& rhs) {
			for (auto& i : (*this)) {
				i *= rhs;
			}
			return (*this);
		}

		/* Vector scalar division.
		*/
		template<typename OtherType>
		auto& operator/=(OtherType const& rhs) {
			for (auto& i : (*this)) {
				i /= rhs;
			}
			return (*this);
		}

	};

	/* Non member function vector sum.
	*/
	template<typename LhsType, typename RhsType, std::size_t N>
	auto operator+(vector<LhsType, N> const& lhs, vector<RhsType, N> const& rhs) {
		using result_type = vector<typename std::common_type<LhsType, RhsType>::type, N>;
		result_type result(lhs);
		result += rhs;
		return result;
	}

	/* Non member function vector subtraction.
	*/
	template<typename LhsType, typename RhsType, std::size_t N>
	auto operator-(vector<LhsType, N> const& lhs, vector<RhsType, N> const& rhs) {
		using result_type = vector<typename std::common_type<LhsType, RhsType>::type, N>;
		result_type result(lhs);
		result -= rhs;
		return result;
	}

	/* Non member function scalar multiplication.
	*/
	template<typename LhsType, std::size_t N, typename RhsType>
	auto operator*(vector<LhsType, N> const& lhs, RhsType const& rhs) {
		using result_type = vector<typename std::common_type<LhsType, RhsType>::type, N>;
		result_type result(lhs);
		result *= rhs;
		return result;
	}

	template<typename LhsType, typename RhsType, std::size_t N>
	auto operator*(LhsType const& lhs, vector<RhsType, N> const& rhs) {
		using result_type = vector<typename std::common_type<LhsType, RhsType>::type, N>;
		result_type result(rhs);
		result *= lhs;
		return result;
	}

	/* Non member function scalar division.
	 * Notice: `scalar / vector` is intentionally not provided given that it doesn't
	 * have clear semantic in this context.
	*/
	template<typename LhsType, std::size_t N, typename RhsType>
	auto operator/(vector<LhsType, N> const& lhs, RhsType const& rhs) {
		using result_type = vector<typename std::common_type<LhsType, RhsType>::type, N>;
		result_type result(lhs);
		result /= rhs;
		return result;
	}
	
}