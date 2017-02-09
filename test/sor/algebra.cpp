#include "../../deps/catch/include/catch.hpp"
#include "../../include/vector.hpp"
#include "../../include/matrix.hpp"
#include "../../include/algebra.hpp"

SCENARIO("vector addition", "[algebra]") {

	GIVEN("few non constant vectors") {

		sor::vector<long, 3> vector1({
			3, 6, 1
		});
		sor::vector<int, 3> vector2({
			7, 3, 6
		});

		WHEN("we add one to the other") {

			vector1 += vector2;

			THEN("the result is stored in the first one") {

				REQUIRE(vector1(0) == 10);
				REQUIRE(vector1(1) == 9);
				REQUIRE(vector1(2) == 7);

			}

			THEN("the second one remains unchanged") {

				REQUIRE(vector2(0) == 7);
				REQUIRE(vector2(1) == 3);
				REQUIRE(vector2(2) == 6);

			}

		}

		WHEN("we add two") {

			auto result = vector1 + vector2;

			THEN("the result is correct") {

				REQUIRE(result(0) == 10);
				REQUIRE(result(1) == 9);
				REQUIRE(result(2) == 7);

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

SCENARIO("vector subtraction", "[algebra]") {

	GIVEN("few non constant vectors") {

		sor::vector<long, 3> vector1({
			3, 6, 1
		});
		sor::vector<int, 3> vector2({
			7, 3, 6
		});

		WHEN("we subtract one to the other") {

			vector1 -= vector2;

			THEN("the result is stored in the first one") {

				REQUIRE(vector1[0] == -4);
				REQUIRE(vector1[1] == 3);
				REQUIRE(vector1[2] == -5);

			}

			THEN("the second one remains unchanged") {

				REQUIRE(vector2(0) == 7);
				REQUIRE(vector2(1) == 3);
				REQUIRE(vector2(2) == 6);

			}

		}

		WHEN("we subtract two") {

			auto result = vector1 - vector2;

			THEN("the result is correct") {

				REQUIRE(result[0] == -4);
				REQUIRE(result[1] == 3);
				REQUIRE(result[2] == -5);

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

SCENARIO("vector scalar product", "[algebra]") {

	GIVEN("a non constant vector") {

		sor::vector<int, 4> vector1({
			4, 7, 2, -2
		});

		WHEN("we multiply it for a scalar and store the result in the same vector") {

			vector1 *= 3;

			THEN("we get the scalar product") {

				REQUIRE(vector1[0] == 12);
				REQUIRE(vector1[1] == 21);
				REQUIRE(vector1[2] == 6);
				REQUIRE(vector1[3] == -6);

			}

		}

		WHEN("we multiply it for a scalar on the right hand side") {

			auto result = vector1 * -2l;

			THEN("the result is correct") {

				REQUIRE(result[0] == -8);
				REQUIRE(result[1] == -14);
				REQUIRE(result[2] == -4);
				REQUIRE(result[3] == 4);

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_long = std::is_same<
					decltype(result)::value_type,
					long
				>::value;
				REQUIRE(is_long);

			}

		}

		WHEN("we multiply it for a scalar on the left hand side") {

			auto result = -2l * vector1;

			THEN("the result is correct") {

				REQUIRE(result[0] == -8);
				REQUIRE(result[1] == -14);
				REQUIRE(result[2] == -4);
				REQUIRE(result[3] == 4);

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

SCENARIO("vector scalar division", "[algebra]") {

	GIVEN("a non constant vector") {

		sor::vector<double, 4> vector1({
			4, 7, 2, -2
		});

		WHEN("we divide for a scalar and store the result in the same vector") {

			vector1 /= 2;

			THEN("we get the scalar product") {

				REQUIRE(vector1[0] == Approx(2));
				REQUIRE(vector1[1] == Approx(3.5));
				REQUIRE(vector1[2] == Approx(1));
				REQUIRE(vector1[3] == Approx(-1));

			}

		}

		WHEN("we divide it for a scalar on the right hand side") {

			auto result = vector1 / -2l;

			THEN("the result is correct") {

				REQUIRE(result[0] == Approx(-2));
				REQUIRE(result[1] == Approx(-3.5));
				REQUIRE(result[2] == Approx(-1));
				REQUIRE(result[3] == Approx(1));

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_double = std::is_same<
					decltype(result)::value_type,
					double
				>::value;
				REQUIRE(is_double);

			}

		}

	}

}

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

SCENARIO("matrix scalar product", "[algebra]") {

	GIVEN("a non constant matrix") {

		sor::matrix<int, 2, 4> matrix({
			4, 7, 2, -2,
			8, 5, -1, 9
		});

		WHEN("we multiply it for a scalar and store the result in the same matrix") {

			matrix *= 3;

			THEN("we get the scalar product") {

				REQUIRE(matrix(0, 0) == 12);
				REQUIRE(matrix(0, 1) == 21);
				REQUIRE(matrix(0, 2) == 6);
				REQUIRE(matrix(0, 3) == -6);
				REQUIRE(matrix(1, 0) == 24);
				REQUIRE(matrix(1, 1) == 15);
				REQUIRE(matrix(1, 2) == -3);
				REQUIRE(matrix(1, 3) == 27);

			}

		}

		WHEN("we multiply it for a scalar on the right hand side") {

			auto result = matrix * -2l;

			THEN("the result is correct") {

				REQUIRE(result(0, 0) == -8);
				REQUIRE(result(0, 1) == -14);
				REQUIRE(result(0, 2) == -4);
				REQUIRE(result(0, 3) == 4);
				REQUIRE(result(1, 0) == -16);
				REQUIRE(result(1, 1) == -10);
				REQUIRE(result(1, 2) == 2);
				REQUIRE(result(1, 3) == -18);

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_long = std::is_same<
					decltype(result)::value_type,
					long
				>::value;
				REQUIRE(is_long);

			}

		}

		WHEN("we multiply it for a scalar on the left hand side") {

			auto result = -2l * matrix;

			THEN("the result is correct") {

				REQUIRE(result(0, 0) == -8);
				REQUIRE(result(0, 1) == -14);
				REQUIRE(result(0, 2) == -4);
				REQUIRE(result(0, 3) == 4);
				REQUIRE(result(1, 0) == -16);
				REQUIRE(result(1, 1) == -10);
				REQUIRE(result(1, 2) == 2);
				REQUIRE(result(1, 3) == -18);

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

SCENARIO("matrix scalar division", "[algebra]") {

	GIVEN("a non constant matrix") {

		sor::matrix<double, 2, 4> matrix({
			4, 7, 2, -2,
			8, 5, -1, 9
		});

		WHEN("we divide for a scalar and store the result in the same matrix") {

			matrix /= 2;

			THEN("we get the scalar product") {

				REQUIRE(matrix(0, 0) == Approx(2));
				REQUIRE(matrix(0, 1) == Approx(3.5));
				REQUIRE(matrix(0, 2) == Approx(1));
				REQUIRE(matrix(0, 3) == Approx(-1));
				REQUIRE(matrix(1, 0) == Approx(4));
				REQUIRE(matrix(1, 1) == Approx(2.5));
				REQUIRE(matrix(1, 2) == Approx(-0.5));
				REQUIRE(matrix(1, 3) == Approx(4.5));

			}

		}

		WHEN("we divide it for a scalar on the right hand side") {

			auto result = matrix / -2l;

			THEN("the result is correct") {

				REQUIRE(result(0, 0) == Approx(-2));
				REQUIRE(result(0, 1) == Approx(-3.5));
				REQUIRE(result(0, 2) == Approx(-1));
				REQUIRE(result(0, 3) == Approx(1));
				REQUIRE(result(1, 0) == Approx(-4));
				REQUIRE(result(1, 1) == Approx(-2.5));
				REQUIRE(result(1, 2) == Approx(0.5));
				REQUIRE(result(1, 3) == Approx(-4.5));

			}

			THEN("the result type is the common type between the two value types") {

				constexpr bool is_double = std::is_same<
					decltype(result)::value_type,
					double
				>::value;
				REQUIRE(is_double);

			}

		}

	}

}