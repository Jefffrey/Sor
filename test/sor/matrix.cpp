#include "../../deps/catch/include/catch.hpp"
#include "../../include/matrix.hpp"

SCENARIO("matrix addition", "[matrix]") {

	GIVEN("few matrices") {

		sor::matrix<long, 2, 3> matrix1({
			3, 6, 1,
			6, 4, 2
		});
		sor::matrix<int, 2, 3> matrix2({
			7, 3, 6,
			1, 12, 34
		});

		WHEN("one matrix is added to the other") {

			matrix1 += matrix2;

			THEN("the result is stored in the first") {
				REQUIRE(matrix1(0, 0) == 10);
				REQUIRE(matrix1(0, 1) == 9);
				REQUIRE(matrix1(0, 2) == 7);
				REQUIRE(matrix1(1, 0) == 7);
				REQUIRE(matrix1(1, 1) == 16);
				REQUIRE(matrix1(1, 2) == 36);
			}

			THEN("the second one remains unchanged") {
				REQUIRE(matrix2(0, 0) == 7);
				REQUIRE(matrix2(0, 1) == 3);
				REQUIRE(matrix2(0, 2) == 6);
				REQUIRE(matrix2(1, 0) == 1);
				REQUIRE(matrix2(1, 1) == 12);
				REQUIRE(matrix2(1, 2) == 34);
			}

		}

		WHEN("we sum two matrices") {

			auto result = matrix1 + matrix2;

			THEN("the result is correct") {

				REQUIRE(result(0, 0) == 10);
				REQUIRE(result(0, 1) == 9);
				REQUIRE(result(0, 2) == 7);
				REQUIRE(result(1, 0) == 7);
				REQUIRE(result(1, 1) == 16);
				REQUIRE(result(1, 2) == 36);

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_long = std::is_same<
					decltype(result)::value_type,
					long
				>::value;
				REQUIRE(is_long);

			}

		}

	}

}

SCENARIO("matrix subtraction", "[matrix]") {

	GIVEN("few matrices") {

		sor::matrix<long, 2, 3> matrix1({
			3, 6, 1,
			6, 4, 2
		});
		sor::matrix<int, 2, 3> matrix2({
			7, 3, 6,
			1, 12, 34
		});

		WHEN("one matrix is subtracted to the other") {

			matrix1 -= matrix2;

			THEN("the result is stored in the first") {
				REQUIRE(matrix1(0, 0) == -4);
				REQUIRE(matrix1(0, 1) == 3);
				REQUIRE(matrix1(0, 2) == -5);
				REQUIRE(matrix1(1, 0) == 5);
				REQUIRE(matrix1(1, 1) == -8);
				REQUIRE(matrix1(1, 2) == -32);
			}

			THEN("the second one remains unchanged") {
				REQUIRE(matrix2(0, 0) == 7);
				REQUIRE(matrix2(0, 1) == 3);
				REQUIRE(matrix2(0, 2) == 6);
				REQUIRE(matrix2(1, 0) == 1);
				REQUIRE(matrix2(1, 1) == 12);
				REQUIRE(matrix2(1, 2) == 34);
			}

		}

		WHEN("we subtract two matrices") {

			auto result = matrix1 - matrix2;

			THEN("the result is correct") {

				REQUIRE(result(0, 0) == -4);
				REQUIRE(result(0, 1) == 3);
				REQUIRE(result(0, 2) == -5);
				REQUIRE(result(1, 0) == 5);
				REQUIRE(result(1, 1) == -8);
				REQUIRE(result(1, 2) == -32);

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_long = std::is_same<
					decltype(result)::value_type,
					long
				>::value;
				REQUIRE(is_long);

			}

		}

	}

}