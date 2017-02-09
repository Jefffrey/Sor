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

	};

	/* Matrix sum.
	*/
	template<typename LhsType, typename RhsType, std::size_t N, std::size_t M>
	auto& operator+=(matrix<LhsType, N, M>& lhs, matrix<RhsType, N, M> const& rhs) {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<void>());
		return lhs;
	}

	template<typename LhsType, typename RhsType, std::size_t N, std::size_t M>
	auto operator+(matrix<LhsType, N, M> const& lhs, matrix<RhsType, N, M> const& rhs) {
		using result_type = matrix<typename std::common_type<LhsType, RhsType>::type, N, M>;
		result_type result(lhs);
		result += rhs;
		return result;
	}

	/* Matrix subtraction.
	*/
	template<typename LhsType, typename RhsType, std::size_t N, std::size_t M>
	auto& operator-=(matrix<LhsType, N, M>& lhs, matrix<RhsType, N, M> const& rhs) {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<void>());
		return lhs;
	}

	template<typename LhsType, typename RhsType, std::size_t N, std::size_t M>
	auto operator-(matrix<LhsType, N, M> const& lhs, matrix<RhsType, N, M> const& rhs) {
		using result_type = matrix<typename std::common_type<LhsType, RhsType>::type, N, M>;
		result_type result(lhs);
		result -= rhs;
		return result;
	}

}