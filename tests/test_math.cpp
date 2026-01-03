#include <catch2/catch_test_macros.hpp>

#include "../src/math.hpp"

TEST_CASE("halfAdd works correctly") {
    auto [sum, carry] = halfAdd(0, 0);
    REQUIRE(sum == 0);
    REQUIRE(carry == 0);

    std::tie(sum, carry) = halfAdd(1, 0);
    REQUIRE(sum == 1);
    REQUIRE(carry == 0);

    std::tie(sum, carry) = halfAdd(1, 1);
    REQUIRE(sum == 0);
    REQUIRE(carry == 1);
}

TEST_CASE("fullAdd handles carry correctly") {
    auto [sum, carry] = fullAdd(1, 1, 0);
    REQUIRE(sum == 0);
    REQUIRE(carry == 1);

    std::tie(sum, carry) = fullAdd(1, 1, 1);
    REQUIRE(sum == 1);
    REQUIRE(carry == 1);
}

TEST_CASE("halfSubtract works correctly") {
    auto [diff, borrow] = halfSubtract(1, 0);
    REQUIRE(diff == 1);
    REQUIRE(borrow == 0);

    std::tie(diff, borrow) = halfSubtract(0, 1);
    REQUIRE(diff == 1);
    REQUIRE(borrow == 1);
}

TEST_CASE("addBinary adds binary strings") {
    REQUIRE(addBinary("0001", "0010") == "0011");
    REQUIRE(addBinary("1111", "0001") == "10000");
}

TEST_CASE("subtractBinary subtracts correctly") {
    REQUIRE(subtractBinary("0100", "0011") == "0001");
}

TEST_CASE("subtractBinary detects negative result") {
    REQUIRE(subtractBinary("0010", "0100") == "ERROR - Negative Result");
}
// Additional test cases can be added as needed