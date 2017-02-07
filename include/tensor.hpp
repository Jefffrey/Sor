#pragma once

#include <algorithm>
#include <type_traits>

#include "type_traits.hpp"
#include "tensor_facade.hpp"

namespace sor {

	template<typename Type, std::size_t... Dims>
	struct tensor : tensor_facade<Type, Dims...> {

		/* Inherit base constructors.
		*/
		using tensor_facade<Type, Dims...>::tensor_facade;

	};

	/* Implementation of the `sor::order` metaprogramming function.
	*/
	template<typename Type, std::size_t... Dims>
	struct order<tensor<Type, Dims...>>
		: public std::integral_constant<std::size_t, sizeof...(Dims)> {};

	/* Implementation of the `sor::extent` metaprogramming function.
	*/
	template<typename Type, std::size_t First, std::size_t... Dims, std::size_t Index>
	struct extent<tensor<Type, First, Dims...>, Index>
		: public std::integral_constant<std::size_t, 
			extent<tensor<Type, Dims...>, Index - 1>::value
		> {};

	template<typename Type, std::size_t First, std::size_t... Dims>
	struct extent<tensor<Type, First, Dims...>, 0>
		: public std::integral_constant<std::size_t, First> {};

	/* Equality operators
	*/
	template<typename LhsType, typename RhsType, std::size_t... LhsDims, std::size_t... RhsDims>
	constexpr bool operator==(tensor<LhsType, LhsDims...> const&, tensor<RhsType, RhsDims...> const&) {
		return false;
	}

	template<typename LhsType, typename RhsType, std::size_t... CommonDims>
	bool operator==(tensor<LhsType, CommonDims...> const& lhs, tensor<RhsType, CommonDims...> const& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename LhsType, typename RhsType, std::size_t... LhsDims, std::size_t... RhsDims>
	constexpr bool operator!=(tensor<LhsType, LhsDims...> const&, tensor<RhsType, RhsDims...> const&) {
		return true;
	}

	template<typename LhsType, typename RhsType, std::size_t... CommonDims>
	bool operator!=(tensor<LhsType, CommonDims...> const& lhs, tensor<RhsType, CommonDims...> const& rhs) {
		return !(lhs == rhs);
	}

	/* Swap function
	*/
	template<typename Type, std::size_t... Dims>
	void swap(tensor<Type, Dims...>& lhs, tensor<Type, Dims...>& rhs) {
		lhs.swap(rhs);
	}

}