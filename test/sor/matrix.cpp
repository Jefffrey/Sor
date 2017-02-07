#include "../../deps/catch/include/catch.hpp"
#include "../../include/matrix.hpp"

TEST_CASE("matrix") {

	SECTION("operator+=") {

		sor::matrix<int, 2, 3> matrix1({
			3, 6, 1,
			6, 4, 2
		});
		sor::matrix<int, 2, 3> matrix2({
			7, 3, 6,
			1, 12, 34
		});
		matrix1 += matrix2;

		REQUIRE(matrix1(0, 0) == 10);
		REQUIRE(matrix1(0, 1) == 9);
		REQUIRE(matrix1(0, 2) == 7);
		REQUIRE(matrix1(1, 0) == 7);
		REQUIRE(matrix1(1, 1) == 16);
		REQUIRE(matrix1(1, 2) == 36);

		REQUIRE(matrix2(0, 0) == 7);
		REQUIRE(matrix2(0, 1) == 3);
		REQUIRE(matrix2(0, 2) == 6);
		REQUIRE(matrix2(1, 0) == 1);
		REQUIRE(matrix2(1, 1) == 12);
		REQUIRE(matrix2(1, 2) == 34);

	}

}