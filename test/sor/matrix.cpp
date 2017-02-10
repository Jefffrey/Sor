#include "../../deps/catch/include/catch.hpp"
#include "../../include/matrix.hpp"

SCENARIO("matrix order query", "[matrix]") {

	GIVEN("a matrix type") {

		using matrix_type = sor::matrix<int, 1, 2>;

		WHEN("we query the order value") {

			constexpr auto order = sor::order<matrix_type>::value;

			THEN("we get 2") {

				REQUIRE(order == 2);

			}

		}

	}

}

SCENARIO("matrix extent query", "[matrix]") {

	GIVEN("a matrix type") {

		using matrix_type = sor::matrix<int, 2, 3>;

		WHEN("we query the extent values") {

			constexpr auto extent1 = sor::extent<matrix_type, 0>::value;
			constexpr auto extent2 = sor::extent<matrix_type, 1>::value;

			THEN("we get the dimensionality of the matrix") {

				REQUIRE(extent1 == 2);
				REQUIRE(extent2 == 3);

			}

		}

	}

}