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

SCENARIO("matrix multiplication", "[matrix]") {

	GIVEN("two matrices") {

		sor::matrix<int, 2, 3> matrix1({
			1, 2, 3,
			4, 5, 6
		});

		sor::matrix<long, 3, 4> matrix2({
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12
		});

		WHEN("we multiply them") {

			auto result = matrix1 * matrix2;

			THEN("the result is the matrix product") {

				sor::matrix<long, 2, 4> expected({
					38, 44, 50, 56,
					83, 98, 113, 128,
					128, 152, 176, 200
				});
				REQUIRE(result == expected);

			}

			THEN("the type is the common value type between the two matrices") {

				constexpr bool is_long = std::is_same<
					decltype(result)::value_type, 
					long
				>::value;
				REQUIRE(is_long);

			}

		}

	}

}