#include "../../deps/catch/include/catch.hpp"
#include "../../include/vector.hpp"

TEST_CASE("vector") {

	SECTION("operator[]") {

		{
			sor::vector<int, 5> const vector({ 3, 4, 7, 12, 5 });
			REQUIRE(vector[0] == 3);
			REQUIRE(vector[1] == 4);
			REQUIRE(vector[2] == 7);
			REQUIRE(vector[3] == 12);
			REQUIRE(vector[4] == 5);
		}

		{
			sor::vector<int, 5> vector({ 3, 4, 7, 12, 5 });
			vector[0] = 6;
			vector[1] = 34;
			vector[2] = 87;
			vector[3] = 1;
			vector[4] = 0;

			REQUIRE(vector[0] == 6);
			REQUIRE(vector[1] == 34);
			REQUIRE(vector[2] == 87);
			REQUIRE(vector[3] == 1);
			REQUIRE(vector[4] == 0);
		}

	}

	SECTION("operator+=") {

		sor::vector<int, 3> vector1({
			3, 6, 1
		});
		sor::vector<int, 3> vector2({
			7, 3, 6
		});
		vector1 += vector2;

		REQUIRE(vector1(0) == 10);
		REQUIRE(vector1(1) == 9);
		REQUIRE(vector1(2) == 7);

		REQUIRE(vector2(0) == 7);
		REQUIRE(vector2(1) == 3);
		REQUIRE(vector2(2) == 6);

	}

}