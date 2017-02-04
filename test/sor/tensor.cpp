#include "../../deps/catch/include/catch.hpp"
#include "../../include/tensor.hpp"

TEST_CASE("tensor", "[tensor]") {

	SECTION("tensor::operator()") {

		{
			sor::tensor<int, 4> tensor({ 5, 8, 2, 4 });
			REQUIRE(tensor(0) == 5);
			REQUIRE(tensor(1) == 8);
			REQUIRE(tensor(2) == 2);
			REQUIRE(tensor(3) == 4);
		}

		{
			sor::tensor<int, 3, 4> tensor({
				4, 5, 7, 2,
				45, 7, 23, 21, 
				98, 3, 56, 12
			});
			REQUIRE(tensor(0, 0) == 4);
			REQUIRE(tensor(0, 1) == 5);
			REQUIRE(tensor(1 ,1) == 7);
			REQUIRE(tensor(1, 0) == 45);
			REQUIRE(tensor(2, 2) == 56);
			REQUIRE(tensor(2, 3) == 12);
		}

	}

}