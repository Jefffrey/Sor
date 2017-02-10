#pragma once

#include <type_traits>

#include "../matrix.hpp"

namespace sor {

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