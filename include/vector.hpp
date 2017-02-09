#pragma once

#include <algorithm>
#include <numeric>
#include <cassert>

#include "tensor_facade.hpp"
#include "tensor.hpp"
#include "algebra.hpp"

namespace sor {

	template<typename Type, std::size_t N>
	using vector = tensor<Type, N>;

	template<typename Type, std::size_t N>
	struct tensor<Type, N> : tensor_facade<Type, N> {

		/* Inherit base constructors and assignment operators.
		*/
		using tensor_facade<Type, N>::tensor_facade;
		using tensor_facade<Type, N>::operator=;

		/* Vector subscript access.
		*/
		Type& operator[](std::size_t i) { return (*this)(i); }
		Type const& operator[](std::size_t i) const { return (*this)(i); }

	};

	/* Component x, y, z, w access.
	*/
	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 0), int>::type = 0>
	auto& x(vector<Type, N>& vector) { return vector[0]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 0), int>::type = 0>
	auto& x(vector<Type, N> const& vector) { return vector[0]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 1), int>::type = 0>
	auto& y(vector<Type, N>& vector) { return vector[1]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 1), int>::type = 0>
	auto& y(vector<Type, N> const& vector) { return vector[1]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 2), int>::type = 0>
	auto& z(vector<Type, N>& vector) { return vector[2]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 2), int>::type = 0>
	auto& z(vector<Type, N> const& vector) { return vector[2]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 3), int>::type = 0>
	auto& w(vector<Type, N>& vector) { return vector[3]; }

	template<typename Type, std::size_t N,
		typename std::enable_if<(N > 3), int>::type = 0>
	auto& w(vector<Type, N> const& vector) { return vector[3]; }

	/* Euclidean norm (magnitude).
	 * The euclidean norm is the length of a vector.
	*/
	template<typename Type, std::size_t N>
	Type euclidean_norm(vector<Type, N> const& vec) {
		auto acc_fn = [](Type const& init, Type const& curr) { return init + std::pow(curr, 2); };
		auto sum = std::accumulate(vec.begin(), vec.end(), Type(), acc_fn);
		return std::sqrt(sum);
	}

	/* Euclidean distance.
	 * @todo: improve space complexity
	*/
	template<typename Type, std::size_t N>
	Type euclidean_distance(vector<Type, N> lhs, vector<Type, N> const& rhs) {
		lhs -= rhs;
		return euclidean_norm(lhs);
	}

	/* Vector normalization.
	*/
	template<typename Type, std::size_t N>
	void normalize(vector<Type, N>& vec) {
		auto norm = euclidean_norm(vec);
		assert(norm != Type());
		for (auto& element : vec) { element /= norm; }
	}
	
}