#include <type_traits>

#include "../../deps/catch/include/catch.hpp"
#include "../../include/vector.hpp"

SCENARIO("vector order query", "[vector]") {

	GIVEN("a vector type") {

		using vector_type = sor::vector<int, 2>;

		WHEN("we query the order value") {

			constexpr auto order = sor::order<vector_type>::value;

			THEN("we get 1") {

				REQUIRE(order == 1);

			}

		}

	}

}

SCENARIO("vector extent query", "[vector]") {

	GIVEN("a vector type") {

		using vector_type = sor::vector<int, 3>;

		WHEN("we query the extent values") {

			constexpr auto extent = sor::extent<vector_type, 0>::value;

			THEN("we get the dimensionality of the matrix") {

				REQUIRE(extent == 3);

			}

		}

	}

}

SCENARIO("vector subscript access", "[vector]") {

	GIVEN("a constant vector") {

		sor::vector<int, 5> const vector({ 3, 4, 7, 12, 5 });

		WHEN("we access an element") {

			THEN("we get the constant reference to that element") {

				REQUIRE(vector[0] == 3);
				REQUIRE(vector[1] == 4);
				REQUIRE(vector[2] == 7);
				REQUIRE(vector[3] == 12);
				REQUIRE(vector[4] == 5);

				constexpr bool is_constant = std::is_same<decltype(vector[0]), int const&>::value;
				REQUIRE(is_constant);

			}

		}

	}

	GIVEN("a non constant vector") {

		sor::vector<int, 5> vector({ 3, 4, 7, 12, 5 });

		WHEN("we modify an element") {

			vector[0] = 6;
			vector[1] = 34;
			vector[2] = 87;
			vector[3] = 1;
			vector[4] = 0;

			THEN("the element is modified") {

				REQUIRE(vector[0] == 6);
				REQUIRE(vector[1] == 34);
				REQUIRE(vector[2] == 87);
				REQUIRE(vector[3] == 1);
				REQUIRE(vector[4] == 0);

			}

		}

	}

}