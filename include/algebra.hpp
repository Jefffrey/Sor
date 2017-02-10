#pragma once

#include "tensor.hpp"

namespace sor {

	/* Vector & matrix nagation.
	*/
	template<typename Type, std::size_t... Dims,
		typename std::enable_if<sizeof...(Dims) < 3, int>::type = 0>
	auto operator-(tensor<Type, Dims...> lhs) {
		std::transform(lhs.begin(), lhs.end(), lhs.begin(), std::negate<void>());
		return lhs;
	}

	/* Vector & matrix sum.
	*/
	template<typename LhsType, typename RhsType, std::size_t... Dims,
		typename std::enable_if<sizeof...(Dims) < 3, int>::type = 0>
	auto& operator+=(tensor<LhsType, Dims...>& lhs, tensor<RhsType, Dims...> const& rhs) {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<void>());
		return lhs;
	}

	template<typename LhsType, typename RhsType, std::size_t... Dims,
		typename std::enable_if<sizeof...(Dims) < 3, int>::type = 0>
	auto operator+(tensor<LhsType, Dims...> const& lhs, tensor<RhsType, Dims...> const& rhs) {
		using result_type = tensor<typename std::common_type<LhsType, RhsType>::type, Dims...>;
		result_type result(lhs);
		result += rhs;
		return result;
	}

	/* Vector & matrix subtraction.
	*/
	template<typename LhsType, typename RhsType, std::size_t... Dims,
		typename std::enable_if<sizeof...(Dims) < 3, int>::type = 0>
	auto& operator-=(tensor<LhsType, Dims...>& lhs, tensor<RhsType, Dims...> const& rhs) {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<void>());
		return lhs;
	}

	template<typename LhsType, typename RhsType, std::size_t... Dims,
		typename std::enable_if<sizeof...(Dims) < 3, int>::type = 0>
	auto operator-(tensor<LhsType, Dims...> const& lhs, tensor<RhsType, Dims...> const& rhs) {
		using result_type = tensor<typename std::common_type<LhsType, RhsType>::type, Dims...>;
		result_type result(lhs);
		result -= rhs;
		return result;
	}

	/* Vector & matrix scalar multiplication.
	*/
	template<typename LhsType, std::size_t... Dims, typename RhsType,
		typename std::enable_if<
			sizeof...(Dims) < 3 && !sor::is_tensor<RhsType>::value, 
			int
		>::type = 0>
	auto& operator*=(tensor<LhsType, Dims...>& lhs, RhsType const& rhs) {
		for (auto& i : lhs) { i *= rhs; }
		return rhs;
	}

	template<typename LhsType, std::size_t... Dims, typename RhsType,
		typename std::enable_if<
			sizeof...(Dims) < 3 && !sor::is_tensor<RhsType>::value, 
			int
		>::type = 0>
	auto operator*(tensor<LhsType, Dims...> const& lhs, RhsType const& rhs) {
		using result_type = tensor<typename std::common_type<LhsType, RhsType>::type, Dims...>;
		result_type result(lhs);
		result *= rhs;
		return result;
	}

	template<typename LhsType, typename RhsType, std::size_t... Dims,
		typename std::enable_if<
			sizeof...(Dims) < 3 && !sor::is_tensor<LhsType>::value, 
			int
		>::type = 0>
	auto operator*(LhsType const& lhs, tensor<RhsType, Dims...> const& rhs) {
		using result_type = tensor<typename std::common_type<LhsType, RhsType>::type, Dims...>;
		result_type result(rhs);
		result *= lhs;
		return result;
	}

	/* Vector & matrix scalar division.
	 * Notice: `scalar / vector` is intentionally not provided given that it doesn't
	 * have clear semantic in this context.
	*/
	template<typename LhsType, std::size_t... Dims, typename RhsType,
		typename std::enable_if<
			sizeof...(Dims) < 3 && !sor::is_tensor<RhsType>::value, 
			int
		>::type = 0>
	auto& operator/=(tensor<LhsType, Dims...>& lhs, RhsType const& rhs) {
		for (auto& i : lhs) { i /= rhs; }
		return rhs;
	}

	template<typename LhsType, std::size_t... Dims, typename RhsType,
		typename std::enable_if<
			sizeof...(Dims) < 3 && !sor::is_tensor<RhsType>::value, 
			int
		>::type = 0>
	auto operator/(tensor<LhsType, Dims...> const& lhs, RhsType const& rhs) {
		using result_type = tensor<typename std::common_type<LhsType, RhsType>::type, Dims...>;
		result_type result(lhs);
		result /= rhs;
		return result;
	}

}