#include "../../deps/catch/include/catch.hpp"
#include "../../include/tensor.hpp"

TEST_CASE("tensor", "[tensor]") {

	SECTION("order") {
		using order1 = sor::order<sor::tensor<int, 1>>;
		using order2 = sor::order<sor::tensor<int, 3, 4>>;
		using order3 = sor::order<sor::tensor<int, 4, 2, 5>>;
		using order4 = sor::order<sor::tensor<int, 7, 1, 34, 56>>;
		REQUIRE(order1::value == 1);
		REQUIRE(order2::value == 2);
		REQUIRE(order3::value == 3);
		REQUIRE(order4::value == 4);
	}

	SECTION("extent") {
		using tensor = sor::tensor<int, 7, 1, 34>;
		using extent0 = sor::extent<tensor, 0>;
		using extent1 = sor::extent<tensor, 1>;
		using extent2 = sor::extent<tensor, 2>;
		REQUIRE(extent0::value == 7);
		REQUIRE(extent1::value == 1);
		REQUIRE(extent2::value == 34);
	}

	SECTION("tensor::operator()") {

		{
			sor::tensor<int, 4> const tensor({ 5, 8, 2, 4 });
			REQUIRE(tensor(0) == 5);
			REQUIRE(tensor(1) == 8);
			REQUIRE(tensor(2) == 2);
			REQUIRE(tensor(3) == 4);
		}

		{
			sor::tensor<int, 3, 4> const tensor({
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

		{
			sor::tensor<int, 3, 4> tensor({
				4, 5, 7, 2,
				45, 7, 23, 21, 
				98, 3, 56, 12
			});
			tensor(0, 0) = 1;
			tensor(0, 1) = 0;
			tensor(0, 2) = 4;
			tensor(2, 3) = 7;
			REQUIRE(tensor(0, 0) == 1);
			REQUIRE(tensor(0, 1) == 0);
			REQUIRE(tensor(0, 2) == 4);
			REQUIRE(tensor(1 ,1) == 7);
			REQUIRE(tensor(1, 0) == 45);
			REQUIRE(tensor(2, 2) == 56);
			REQUIRE(tensor(2, 3) == 7);
		}

	}

}