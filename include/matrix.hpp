#pragma once

#include "type_traits.hpp"
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

	/* Matrix multiplication.
	*/
	template<typename LhsType, typename RhsType, std::size_t M, std::size_t N, std::size_t P>
	auto operator*(matrix<LhsType, M, N>& lhs, matrix<RhsType, N, P> const& rhs) {
		using common_type = typename std::common_type<LhsType, RhsType>::type;
		using result_type = matrix<common_type, M, P>;
		result_type result;
		for (std::size_t m = 0; m < M; ++m) {
			for (std::size_t p = 0; p < P; ++p) {
				result(m, p) = common_type();
				for (std::size_t n = 0; n < N; ++n) {
					result(m, p) += (lhs(m, n) * rhs(n, p));
				}
			}
		}
		return result;
	}

}