#pragma once

#include <array>
#include <type_traits>
#include <algorithm>

namespace sor {

	template<typename Type, std::size_t... Indexes>
	struct tensor;

	namespace detail {

		/*	Metaprogramming function that calculates the multiplication of all integers
		 * 	passed to it.
		 * 	Example:
		 * 		std::cout << multiply<2, 3, 4>::value;
		 *		// = 2 * 3 * 4 = 24;
		*/
		template<std::size_t N, std::size_t... Ms>
		struct multiply 
			: public std::integral_constant<std::size_t, N * multiply<Ms...>::value> {};

		template<std::size_t N>
		struct multiply<N> 
			: public std::integral_constant<std::size_t, N> {};

	}

	/* The rank of a tensor is the dimensionality or number of dimensions that are
	 * contained in it. That is, the number of indexes you need to use to specify
	 * a specific element in the tensor.
	 * Example:
	 * 		std::cout << std::rank<sor::tensor<int, 5>>::value; 		// 1
	 * 		std::cout << std::rank<sor::tensor<int, 7, 4>>::value;		// 2
	 * 		std::cout << std::rank<sor::tensor<int, 2, 9, 4>>::value;	// 3
	*/
	template<typename TensorType>
	struct rank;

	template<typename Type, std::size_t... Dims>
	struct rank<tensor<Type, Dims...>>
		: public std::integral_constant<std::size_t, sizeof...(Dims)> {};

	/* The tansor class.
	*/
	template<typename Type, std::size_t... Dims>
	struct tensor {

		using tensor_type = tensor<Type, Dims...>;

		/*	Returns the Nth dimension of the tensor.
		 * 	Example:
		 * 		using tensor_type = sor::tensor<int, 2, 3, 4>; // set of 2 3x4 matrices
		 * 		std::cout << tensor_type::dimension<0>; // = 2
		 * 		std::cout << tensor_type::dimension<1>; // = 3
		 * 		std::cout << tensor_type::dimension<2>; // = 4
		*/
		template<std::size_t Index, std::size_t First, std::size_t... Rest>
		struct dimension
			: public std::integral_constant<std::size_t, dimension<Index - 1, Rest...>::value> {};

		template<std::size_t First, std::size_t... Rest>
		struct dimension<0, First, Rest...>
			: public std::integral_constant<std::size_t, First> {};

		/* Regular default, copy and move constructors work as you would expect.
		*/
		tensor() = default;
		tensor(tensor_type const&) = default;
		tensor(tensor_type&&) = default;

		/* Constructor that initializes the array as if you were to initialize an array of multiple
		 * dimensions (left to right, top to bottom, front to back, etc...).
		*/
		tensor(std::initializer_list<Type> const& list) {
			std::copy(list.begin(), list.end(), array.begin());
		}

		/* Copy and move assignment work as you would normally expect.
		*/
		tensor_type& operator=(tensor_type const&) = default;
		tensor_type& operator=(tensor_type&&) = default;

		/* Element access operator. It access the member based on the given indexes.
		 * Example:
		 * 		sor::tensor<int, 3, 4> matrix({
		 * 			0, 1, 2, 3,
		 * 			4, 5, 6, 7,
		 * 			8, 9, 10, 11
		 * 		});
		 *		std::cout << matrix(2, 2); // = 6
		 * @todo: enable only if the number of arguments is equal to the rank
		*/
		template<typename... Args>
		Type& operator()(Args... args) {

			std::initializer_list<std::size_t> indexes = { static_cast<std::size_t>(args)... };
			std::initializer_list<std::size_t> dimensions = { Dims... };

			std::size_t index = 0;
			auto last_index = indexes.end() - 1;
			for (
					auto i = indexes.begin(), d = dimensions.end() - 1; 
					i < last_index && d >= dimensions.begin(); 
					i++, d--
				) {
				index += *i;
				index *= *d;
			}
			index += *last_index;

			return array[index];

		}

	private:


		std::array<Type, detail::multiply<Dims...>::value> array;

	};

}