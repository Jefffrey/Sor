#include "../../../deps/catch/include/catch.hpp"
#include "../../../include/matrix.hpp"
#include "../../../include/algebra/matrix.hpp"

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