#include <type_traits>

#include "../../deps/catch/include/catch.hpp"
#include "../../include/vector.hpp"

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

SCENARIO("vector addition", "[vector]") {

	GIVEN("few non constant vectors") {

		sor::vector<int, 3> vector1({
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

	}

}

SCENARIO("vector subtraction", "[vector]") {

	GIVEN("few non constant vectors") {

		sor::vector<int, 3> vector1({
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

	}

}

SCENARIO("vector scalar product", "[vector]") {

	GIVEN("a non constant vector") {

		sor::vector<int, 4> vector1({
			4, 7, 2, -2
		});

		WHEN("we multiply it for a scalar") {

			vector1 *= 3;

			THEN("we get the scalar product") {

				REQUIRE(vector1[0] == 12);
				REQUIRE(vector1[1] == 21);
				REQUIRE(vector1[2] == 6);
				REQUIRE(vector1[3] == -6);

			}

		}

	}

}

SCENARIO("vector scalar division", "[vector]") {

	GIVEN("a non constant vector") {

		sor::vector<double, 4> vector1({
			4, 7, 2, -2
		});

		WHEN("we multiply it for a scalar") {

			vector1 /= 2;

			THEN("we get the scalar product") {

				REQUIRE(vector1[0] == Approx(2));
				REQUIRE(vector1[1] == Approx(3.5));
				REQUIRE(vector1[2] == Approx(1));
				REQUIRE(vector1[3] == Approx(-1));

			}

		}

	}

}