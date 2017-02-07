#include <type_traits>

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

	GIVEN("a tensor") {

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

			auto es = elements.begin();
			auto ts = tensor.begin();

			THEN("we get them in the order given at construction") {

				for (; es < elements.end() && ts < tensor.end(); ++es, ++ts) {
					REQUIRE(*es == *ts);
				}

			}

		}

		WHEN("we access its elements via constant iterators") {

			auto es = elements.begin();
			auto ts = tensor.cbegin();

			THEN("we get them in the order given at construction") {

				for (; es < elements.end() && ts < tensor.cend(); ++es, ++ts) {
					REQUIRE(*es == *ts);
				}

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

			for (auto& i : tensor) {
				i = 0;
			}

			THEN("they are modified in the tensor") {

				for (auto const& i : tensor) {
					REQUIRE(i == 0);
				}

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

			auto es = elements.begin();
			auto ts = tensor.begin();

			THEN("we get them in the order given at construction") {

				for (; es < elements.end() && ts < tensor.end(); ++es, ++ts) {
					REQUIRE(*es == *ts);
				}

			}

		}

		WHEN("we access its elements via constant iterators") {

			auto es = elements.begin();
			auto ts = tensor.cbegin();

			THEN("we get them in the order given at construction") {

				for (; es < elements.end() && ts < tensor.cend(); ++es, ++ts) {
					REQUIRE(*es == *ts);
				}

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