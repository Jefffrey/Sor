#include <type_traits>
#include <algorithm>

#include "../../deps/catch/include/catch.hpp"
#include "../../include/tensor.hpp"

SCENARIO("tensor order query", "[tensor]") {

	GIVEN("few different tensor types") {

		using tensor1 = sor::tensor<int, 1>;
		using tensor2 = sor::tensor<int, 3, 4>;
		using tensor3 = sor::tensor<int, 4, 2, 5>;
		using tensor4 = sor::tensor<int, 7, 1, 34, 56>;

		WHEN("we query the order value") {

			using order1 = sor::order<tensor1>;
			using order2 = sor::order<tensor2>;
			using order3 = sor::order<tensor3>;
			using order4 = sor::order<tensor4>;

			THEN("we get the dimensionality of the tensor") {

				REQUIRE(order1::value == 1);
				REQUIRE(order2::value == 2);
				REQUIRE(order3::value == 3);
				REQUIRE(order4::value == 4);

			}

		}

	}

}

SCENARIO("tensor extent query", "[tensor]") {

	GIVEN("a tensor type") {

		using tensor = sor::tensor<int, 7, 1, 34>;

		WHEN("we query the extent of a dimension") {

			using extent0 = sor::extent<tensor, 0>;
			using extent1 = sor::extent<tensor, 1>;
			using extent2 = sor::extent<tensor, 2>;

			THEN("we get the length of that dimension") {

				REQUIRE(extent0::value == 7);
				REQUIRE(extent1::value == 1);
				REQUIRE(extent2::value == 34);

			}

		}

	}

}

SCENARIO("tensor value type definitions", "[tensor]") {

	GIVEN("a tensor type") {

		using tensor = sor::tensor<unsigned int, 7, 1, 34>;

		WHEN("we query its value type") {

			using type = tensor::value_type;

			THEN("we get the type of the elements") {

				constexpr bool are_equal = std::is_same<
					type,
					unsigned int
				>::value;
				REQUIRE(are_equal);

			}

		}

		WHEN("we query its reference type") {

			using type = tensor::reference;

			THEN("we get the reference type to the type of the elements") {

				constexpr bool are_equal = std::is_same<
					type,
					unsigned int&
				>::value;
				REQUIRE(are_equal);

			}

		}

		WHEN("we query its constant reference type") {

			using type = tensor::const_reference;

			THEN("we get the constant reference type to the type of the elements") {

				constexpr bool are_equal = std::is_same<
					type,
					unsigned int const&
				>::value;
				REQUIRE(are_equal);

			}

		}

	}

}

SCENARIO("tensor constructors", "[tensor]") {

	GIVEN("an initializer list") {

		std::initializer_list<int> list({ 2, 3, 4, 5, 6, 7});

		WHEN("we construct a tensor with said list") {

			sor::tensor<long, 2, 3> tensor(list);

			THEN("the tensor is filled with the elements of the list") {

				REQUIRE(tensor(0, 0) == 2);
				REQUIRE(tensor(0, 1) == 3);
				REQUIRE(tensor(0, 2) == 4);
				REQUIRE(tensor(1, 0) == 5);
				REQUIRE(tensor(1, 1) == 6);
				REQUIRE(tensor(1, 2) == 7);

			}

			THEN("the list remains unchanged") {

				auto it = list.begin();
				REQUIRE(*(it++) == 2);
				REQUIRE(*(it++) == 3);
				REQUIRE(*(it++) == 4);
				REQUIRE(*(it++) == 5);
				REQUIRE(*(it++) == 6);
				REQUIRE(*(it++) == 7);

			}

		}

	}

	GIVEN("a tensor") {

		sor::tensor<int, 2, 3> tensor1({
			4, 5, 7,
			45, 7, 23
		});

		WHEN("we construct one with another of the same dimensionality") {

			sor::tensor<long, 2, 3> tensor2(tensor1);

			THEN("one is copied into the other") {

				REQUIRE(tensor2(0, 0) == 4);
				REQUIRE(tensor2(0, 1) == 5);
				REQUIRE(tensor2(0, 2) == 7);
				REQUIRE(tensor2(1, 0) == 45);
				REQUIRE(tensor2(1, 1) == 7);
				REQUIRE(tensor2(1, 2) == 23);

			}

			THEN("the other remains unchanged") {

				REQUIRE(tensor1(0, 0) == 4);
				REQUIRE(tensor1(0, 1) == 5);
				REQUIRE(tensor1(0, 2) == 7);
				REQUIRE(tensor1(1, 0) == 45);
				REQUIRE(tensor1(1, 1) == 7);
				REQUIRE(tensor1(1, 2) == 23);

			}

		}

	}

}

SCENARIO("tensor assignment operator", "[tensor]") {

	GIVEN("an initializer list") {

		std::initializer_list<int> list({ 2, 3, 4, 5, 6, 7});

		WHEN("we assign a tensor to the list") {

			sor::tensor<long, 2, 3> tensor;
			tensor = list;

			THEN("the tensor is filled with the elements of the list") {

				REQUIRE(tensor(0, 0) == 2);
				REQUIRE(tensor(0, 1) == 3);
				REQUIRE(tensor(0, 2) == 4);
				REQUIRE(tensor(1, 0) == 5);
				REQUIRE(tensor(1, 1) == 6);
				REQUIRE(tensor(1, 2) == 7);

			}

			THEN("the list remains unchanged") {

				auto it = list.begin();
				REQUIRE(*(it++) == 2);
				REQUIRE(*(it++) == 3);
				REQUIRE(*(it++) == 4);
				REQUIRE(*(it++) == 5);
				REQUIRE(*(it++) == 6);
				REQUIRE(*(it++) == 7);

			}

		}

	}

	GIVEN("two vectors of different types but same dimensionality") {

		sor::tensor<int, 2, 3> tensor1({
			4, 5, 7,
			45, 7, 23
		});

		sor::tensor<long, 2, 3> tensor2({
			6l, -5l, 17l,
			9l, 3l, 2l
		});

		WHEN("we assign one to the other") {

			tensor2 = tensor1;

			THEN("one is copied into the other") {

				REQUIRE(tensor2(0, 0) == 4);
				REQUIRE(tensor2(0, 1) == 5);
				REQUIRE(tensor2(0, 2) == 7);
				REQUIRE(tensor2(1, 0) == 45);
				REQUIRE(tensor2(1, 1) == 7);
				REQUIRE(tensor2(1, 2) == 23);

			}

			THEN("the other remains unchanged") {

				REQUIRE(tensor1(0, 0) == 4);
				REQUIRE(tensor1(0, 1) == 5);
				REQUIRE(tensor1(0, 2) == 7);
				REQUIRE(tensor1(1, 0) == 45);
				REQUIRE(tensor1(1, 1) == 7);
				REQUIRE(tensor1(1, 2) == 23);

			}

		}

	}

}

SCENARIO("tensor access operator", "[tensor]") {

	GIVEN("a constant tensor") {

		sor::tensor<int, 3, 4> const tensor({
			4, 5, 7, 2,
			45, 7, 23, 21, 
			98, 3, 56, 12
		});

		WHEN("we access an element") {

			THEN("we get the constant value of the element") {

				REQUIRE(tensor(0, 0) == 4);
				REQUIRE(tensor(0, 1) == 5);
				REQUIRE(tensor(1 ,1) == 7);
				REQUIRE(tensor(1, 0) == 45);
				REQUIRE(tensor(2, 2) == 56);
				REQUIRE(tensor(2, 3) == 12);

				constexpr bool is_constant = std::is_same<decltype(tensor(0, 0)), int const&>::value;
				REQUIRE(is_constant);

			}

		}

	}

	GIVEN("a non constant tensor") {

		sor::tensor<int, 3, 4> tensor({
			4, 5, 7, 2,
			45, 7, 23, 21, 
			98, 3, 56, 12
		});

		WHEN("we modify some of its elements") {

			tensor(0, 0) = 1;
			tensor(0, 1) = 0;
			tensor(0, 2) = 4;
			tensor(2, 3) = 7;

			THEN("those modifications are reflected in the tensor") {

				REQUIRE(tensor(0, 0) == 1);
				REQUIRE(tensor(0, 1) == 0);
				REQUIRE(tensor(0, 2) == 4);
				REQUIRE(tensor(2, 3) == 7);

			}

			THEN("the other elements are not modified") {

				REQUIRE(tensor(0, 3) == 2);
				REQUIRE(tensor(1, 0) == 45);
				REQUIRE(tensor(1, 1) == 7);
				REQUIRE(tensor(1, 2) == 23);
				REQUIRE(tensor(1, 3) == 21);
				REQUIRE(tensor(2, 0) == 98);
				REQUIRE(tensor(2, 1) == 3);
				REQUIRE(tensor(2, 2) == 56);

			}

		}

	}

}

SCENARIO("tensor iterators", "[tensor]") {

	GIVEN("a non constant tensor") {

		std::initializer_list<int> elements = {
			4, 5, 7, 2,
			45, 7, 23, 21, 
			98, 3, 56, 12
		};
		sor::tensor<int, 3, 4> tensor(elements);

		WHEN("we access its elements via iterators") {

			bool are_equal = std::equal(
				tensor.begin(), tensor.end(), 
				elements.begin(), elements.end()
			);

			THEN("we get them in the order given at construction") {

				REQUIRE(are_equal);

			}

		}

		WHEN("we access its elements via constant iterators") {

			bool are_equal = std::equal(
				tensor.cbegin(), tensor.cend(), 
				elements.begin(), elements.end()
			);

			THEN("we get them in the order given at construction") {

				REQUIRE(are_equal);

			}

			THEN("the iterator type is constant") {

				constexpr bool is_constant_iterator = std::is_same<
					decltype(tensor.cbegin()), 
					sor::tensor<int, 3, 4>::const_iterator
				>::value;
				REQUIRE(is_constant_iterator);

			}

			THEN("the reference from the iterator is constant") {

				constexpr bool is_constant_value = std::is_same<
					decltype(*(tensor.cbegin())), 
					int const&
				>::value;
				REQUIRE(is_constant_value);

			}

		}

		WHEN("we modify its elements via iterators") {

			std::initializer_list<int> new_elements = {
				6, 1, 34, 0,
				-3, 5, 34, -2, 
				-76, 234, 12, -12
			};
			std::copy(new_elements.begin(), new_elements.end(), tensor.begin());

			THEN("they are modified in the tensor") {

				bool are_equal = std::equal(
					tensor.cbegin(), tensor.cend(), 
					new_elements.begin(), new_elements.end()
				);
				REQUIRE(are_equal);

			}

		}

	}

	GIVEN("a constant tensor") {

		std::initializer_list<int> elements = {
			4, 5, 7, 2,
			45, 7, 23, 21, 
			98, 3, 56, 12
		};
		sor::tensor<int, 3, 4> const tensor(elements);

		WHEN("we access its elements via iterators") {

			bool are_equal = std::equal(
				tensor.begin(), tensor.end(), 
				elements.begin(), elements.end()
			);

			THEN("we get them in the order given at construction") {

				REQUIRE(are_equal);

			}

		}

		WHEN("we access its elements via constant iterators") {

			bool are_equal = std::equal(
				tensor.cbegin(), tensor.cend(), 
				elements.begin(), elements.end()
			);

			THEN("we get them in the order given at construction") {

				REQUIRE(are_equal);

			}

			THEN("the iterator type is constant") {

				constexpr bool is_constant_iterator = std::is_same<
					decltype(tensor.cbegin()), 
					sor::tensor<int, 3, 4>::const_iterator
				>::value;
				REQUIRE(is_constant_iterator);

			}

			THEN("the reference from the iterator is constant") {

				constexpr bool is_constant_value = std::is_same<
					decltype(*(tensor.cbegin())), 
					int const&
				>::value;
				REQUIRE(is_constant_value);

			}

		}

	}

}

SCENARIO("tensor underlying data access", "[tensor]") {

	GIVEN("a non constant tensor") {

		sor::tensor<int, 2, 3> tensor({
			1, 2, 3,
			4, 5, 6
		});

		WHEN("we modify the underlying array") {

			int* ptr = tensor.data();
			ptr[0] = 7;
			ptr[1] = 8;
			ptr[2] = 9;
			ptr[3] = 10;
			ptr[4] = 11;
			ptr[5] = 12;

			THEN("the changes are reflected in the tensor") {

				sor::tensor<int, 2, 3> expected({
					7, 8, 9,
					10, 11, 12
				});
				REQUIRE(tensor == expected);

			}

		}

	}

	GIVEN("a constant tensor") {

		sor::tensor<int, 2, 3> const tensor({
			1, 2, 3,
			4, 5, 6
		});

		WHEN("we access the underlying array") {

			int const* ptr = tensor.data();

			THEN("we can read the array sequentially") {

				REQUIRE(ptr[0] == 1);
				REQUIRE(ptr[1] == 2);
				REQUIRE(ptr[2] == 3);
				REQUIRE(ptr[3] == 4);
				REQUIRE(ptr[4] == 5);
				REQUIRE(ptr[5] == 6);

			}

		}

	}

}

SCENARIO("tensor equality", "[tensor]") {

	GIVEN("two equal tensors") {

		sor::tensor<int, 4, 3> tensor1({
			3, 6, 2,
			5, 7, 4,
			7, 9, 23,
			34, 5, 12
		});
		sor::tensor<int, 4, 3> tensor2({
			3, 6, 2,
			5, 7, 4,
			7, 9, 23,
			34, 5, 12
		});

		WHEN("we test for equality") {

			bool are_equal = tensor1 == tensor2;

			THEN("the result is positive") {

				REQUIRE(are_equal);

			}

		}

		WHEN("we test for inequality") {

			bool are_unequal = tensor1 != tensor2;

			THEN("the result is negative") {

				REQUIRE(!are_unequal);

			}

		}

	}

	GIVEN("two different tensors") {

		sor::tensor<int, 4, 3> tensor1({
			3, 6, 2,
			5, 7, 4,
			7, 9, 23,
			34, 5, 12
		});
		sor::tensor<int, 4, 3> tensor2({
			3, 6, 1,
			5, 4, 4,
			2, 9, 23,
			34, 7, 12
		});

		WHEN("we test for equality") {

			bool are_equal = tensor1 == tensor2;

			THEN("the result is negative") {

				REQUIRE(!are_equal);

			}

		}

		WHEN("we test for inequality") {

			bool are_unequal = tensor1 != tensor2;

			THEN("the result is positive") {

				REQUIRE(are_unequal);

			}

		}

	}

	GIVEN("two tensors with different orders") {

		sor::tensor<int, 4> tensor1({ 3, 6, 2, 5 });
		sor::tensor<int, 4, 3> tensor2({
			3, 6, 1,
			5, 4, 4,
			2, 9, 23,
			34, 7, 12
		});

		WHEN("we test for equality") {

			constexpr bool are_equal = tensor1 == tensor2;

			THEN("the result is negative") {

				REQUIRE(!are_equal);

			}

		}

		WHEN("we test for inequality") {

			constexpr bool are_unequal = tensor1 != tensor2;

			THEN("the result is positive") {

				REQUIRE(are_unequal);

			}

		}

	}

	GIVEN("two tensors with different dimensionality") {

		sor::tensor<int, 3, 4> tensor1({
			3, 6, 1, 5, 
			4, 4, 2, 9, 
			23, 34, 7, 12
		});
		sor::tensor<int, 4, 3> tensor2({
			3, 6, 1,
			5, 4, 4,
			2, 9, 23,
			34, 7, 12
		});

		WHEN("we test for equality") {

			constexpr bool are_equal = tensor1 == tensor2;

			THEN("the result is negative") {

				REQUIRE(!are_equal);

			}

		}

		WHEN("we test for inequality") {

			constexpr bool are_unequal = tensor1 != tensor2;

			THEN("the result is positive") {

				REQUIRE(are_unequal);

			}

		}

	}

}

SCENARIO("tensor swap", "[tensor]") {

	GIVEN("two tensors") {

		sor::tensor<int, 2, 3> tensor1({
			3, 56, 6,
			1, 0, -3
		});
		sor::tensor<int, 2, 3> tensor2({
			6, -5, 45,
			-9, -34, 65
		});

		WHEN("we swap them with the member function") {

			tensor1.swap(tensor2);

			THEN("the first tensor is equal to the previous second") {

				bool condition =
					tensor1(0, 0) == 6 &&
					tensor1(0, 1) == -5 &&
					tensor1(0, 2) == 45 &&
					tensor1(1, 0) == -9 &&
					tensor1(1, 1) == -34 &&
					tensor1(1, 2) == 65;
				REQUIRE(condition);

			}

			THEN("the second tensor is equal to the previous first") {

				bool condition =
					tensor2(0, 0) == 3 &&
					tensor2(0, 1) == 56 &&
					tensor2(0, 2) == 6 &&
					tensor2(1, 0) == 1 &&
					tensor2(1, 1) == 0 &&
					tensor2(1, 2) == -3;
				REQUIRE(condition);

			}

		}

		WHEN("we swap them with the non-member functions") {

			std::swap(tensor1, tensor2);

			THEN("the first tensor is equal to the previous second") {

				bool condition =
					tensor1(0, 0) == 6 &&
					tensor1(0, 1) == -5 &&
					tensor1(0, 2) == 45 &&
					tensor1(1, 0) == -9 &&
					tensor1(1, 1) == -34 &&
					tensor1(1, 2) == 65;
				REQUIRE(condition);

			}

			THEN("the second tensor is equal to the previous first") {

				bool condition =
					tensor2(0, 0) == 3 &&
					tensor2(0, 1) == 56 &&
					tensor2(0, 2) == 6 &&
					tensor2(1, 0) == 1 &&
					tensor2(1, 1) == 0 &&
					tensor2(1, 2) == -3;
				REQUIRE(condition);

			}

		}

	}

}

SCENARIO("tensor size") {

	GIVEN("a non empty tensor") {

		sor::tensor<int, 3, 5, 2> tensor;

		WHEN("we query for its size") {

			constexpr auto size = tensor.size();

			THEN("we get the total number of elements in the tensor") {

				REQUIRE(size == 30);

			}

		}

		WHEN("we query for its maximum size") {

			constexpr auto max_size = tensor.max_size();

			THEN("we get the total number of elements in the tensor") {

				REQUIRE(max_size == 30);

			}

		}

		WHEN("we query whether it's empty or not") {

			constexpr auto is_empty = tensor.empty();

			THEN("we get false") {

				REQUIRE(!is_empty);

			}

		}

	}

	GIVEN("an empty tensor") {

		sor::tensor<int, 0, 1> tensor;

		WHEN("we query for its size") {

			constexpr auto size = tensor.size();

			THEN("we get 0") {

				REQUIRE(size == 0);

			}

		}

		WHEN("we query for its maximum size") {

			constexpr auto max_size = tensor.max_size();

			THEN("we get 0") {

				REQUIRE(max_size == 0);

			}

		}

		WHEN("we query whether it's empty or not") {

			constexpr auto is_empty = tensor.empty();

			THEN("we get true") {

				REQUIRE(is_empty);

			}

		}

	}

}