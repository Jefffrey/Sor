#pragma once

namespace sor {

	/* The order of a tensor is the dimensionality or number of dimensions that are
	 * contained in it. That is, the number of indexes you need to use to specify
	 * a specific element in the tensor.
	 * Note: A rank has usually another meaning and should not be mixed with the meaning
	 * of "order".
	 * Example:
	 * 		std::cout << std::order<sor::tensor<int, 5>>::value; 		// 1
	 * 		std::cout << std::order<sor::tensor<int, 7, 4>>::value;		// 2
	 * 		std::cout << std::order<sor::tensor<int, 2, 9, 4>>::value;	// 3
	*/
	template<typename TensorType>
	struct order;

	/*	Metaprogramming function that returns the nth dimension of a tensor.
	 * 	Example:
	 * 		using tensor_type = sor::tensor<int, 2, 3, 4>; // set of 2 3x4 matrices
	 * 		std::cout << sor::extent<tensor_type, 0>::value; // = 2
	 * 		std::cout << sor::extent<tensor_type, 1>::value; // = 3
	 * 		std::cout << sor::extent<tensor_type, 2>::value; // = 4
	*/
	template<typename TensorType, std::size_t Index>
	struct extent;

	/* Meta programming function that returns true if the type passed in is a tensor
	 * and therefore meets the Tensor requirements.
	*/
	template<typename Type>
	struct is_tensor : std::false_type {};

}