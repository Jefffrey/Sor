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

SCENARIO("vector x, y, z, w element access", "[vector]") {

	GIVEN("few constant vectors") {

		sor::vector<int, 1> const vector1({ 1 });
		sor::vector<int, 2> const vector2({ 2, 3 });
		sor::vector<int, 3> const vector3({ 4, 5, 6 });
		sor::vector<int, 4> const vector4({ 7, 8, 9, 10 });
		sor::vector<int, 5> const vector5({ 11, 12, 13, 14, 15 });

		WHEN("we access the x element") {

			THEN("we get a reference to the first element") {

				REQUIRE(sor::x(vector1) == vector1[0]);
				REQUIRE(sor::x(vector2) == vector2[0]);
				REQUIRE(sor::x(vector3) == vector3[0]);
				REQUIRE(sor::x(vector4) == vector4[0]);
				REQUIRE(sor::x(vector5) == vector5[0]);

			}

			THEN("the reference is constant") {

				constexpr bool is_constant = std::is_same<
					decltype(sor::x(vector1)), 
					int const&
				>::value;
				REQUIRE(is_constant);

			}

		}

		WHEN("we access the y element") {

			THEN("we get a reference to the second element") {

				REQUIRE(sor::y(vector2) == vector2[1]);
				REQUIRE(sor::y(vector3) == vector3[1]);
				REQUIRE(sor::y(vector4) == vector4[1]);
				REQUIRE(sor::y(vector5) == vector5[1]);

			}

			THEN("the reference is constant") {

				constexpr bool is_constant = std::is_same<
					decltype(sor::y(vector2)), 
					int const&
				>::value;
				REQUIRE(is_constant);

			}

		}

		WHEN("we access the z element") {

			THEN("we get a reference to the third element") {

				REQUIRE(sor::z(vector3) == vector3[2]);
				REQUIRE(sor::z(vector4) == vector4[2]);
				REQUIRE(sor::z(vector5) == vector5[2]);

			}

			THEN("the reference is constant") {

				constexpr bool is_constant = std::is_same<
					decltype(sor::z(vector3)), 
					int const&
				>::value;
				REQUIRE(is_constant);

			}

		}

		WHEN("we access the w element") {

			THEN("we get a reference to the fourth element") {

				REQUIRE(sor::w(vector4) == vector4[3]);
				REQUIRE(sor::w(vector5) == vector5[3]);

			}

			THEN("the reference is constant") {

				constexpr bool is_constant = std::is_same<
					decltype(sor::w(vector4)), 
					int const&
				>::value;
				REQUIRE(is_constant);

			}

		}


	}

	GIVEN("few non constant vectors") {

		sor::vector<int, 1> vector1({ 1 });
		sor::vector<int, 2> vector2({ 2, 3 });
		sor::vector<int, 3> vector3({ 4, 5, 6 });
		sor::vector<int, 4> vector4({ 7, 8, 9, 10 });
		sor::vector<int, 5> vector5({ 11, 12, 13, 14, 15 });

		WHEN("we modify the x element") {

			sor::x(vector1) = -1;
			sor::x(vector2) = -2;
			sor::x(vector3) = -4;
			sor::x(vector4) = -7;
			sor::x(vector5) = -11;

			THEN("the element is modified") {

				REQUIRE(vector1[0] == -1);
				REQUIRE(vector2[0] == -2);
				REQUIRE(vector3[0] == -4);
				REQUIRE(vector4[0] == -7);
				REQUIRE(vector5[0] == -11);

			}

		}

		WHEN("we modify the y element") {

			sor::y(vector2) = -3;
			sor::y(vector3) = -5;
			sor::y(vector4) = -8;
			sor::y(vector5) = -12;

			THEN("the element is modified") {

				REQUIRE(vector2[1] == -3);
				REQUIRE(vector3[1] == -5);
				REQUIRE(vector4[1] == -8);
				REQUIRE(vector5[1] == -12);

			}

		}

		WHEN("we modify the z element") {

			sor::z(vector3) = -6;
			sor::z(vector4) = -9;
			sor::z(vector5) = -13;

			THEN("the element is modified") {

				REQUIRE(vector3[2] == -6);
				REQUIRE(vector4[2] == -9);
				REQUIRE(vector5[2] == -13);

			}

		}

		WHEN("we modify the w element") {

			sor::w(vector4) = -10;
			sor::w(vector5) = -14;

			THEN("the element is modified") {

				REQUIRE(vector4[3] == -10);
				REQUIRE(vector5[3] == -14);

			}

		}

	}

}

SCENARIO("euclidean norm", "[vector]") {

	GIVEN("a vector") {

		sor::vector<double, 2> vector({ 28.0, 65.0 });

		WHEN("we calculate the euclidean norm") {

			auto result = sor::euclidean_norm(vector);

			THEN("the result is the length of the vector") {

				REQUIRE(result == Approx(70.7742891169));

			}

		}

	}

}

SCENARIO("euclidean distance", "[vector]") {

	GIVEN("a couple of vectors") {

		sor::vector<double, 2> vector1({ 28.0, 65.0 });
		sor::vector<double, 2> vector2({ 2.0, -45.0 });

		WHEN("we calculate the euclidean distance") {

			auto result = sor::euclidean_distance(vector1, vector2);

			THEN("we get the distance between the two vectors") {

				REQUIRE(result == Approx(113.03096920755833));

			}

		}

	}

}