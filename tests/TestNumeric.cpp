
#include <catch2/catch_all.hpp>

#include "TungstenUtils/numeric.hpp"

TEST_CASE("Min integers", "[Min]")
{
    REQUIRE(wUtils::Min(0, 1) == 0);
    REQUIRE(wUtils::Min(1, -1) == -1);
    REQUIRE(wUtils::Min(10, -23405) == -23405);
    REQUIRE(wUtils::Min(142930, 142931) == 142930);
    REQUIRE(wUtils::Min(-142930, 142931) == -142930);
    REQUIRE(wUtils::Min(-14930, -12) == -14930);
}

TEST_CASE("Min floats", "[Min]")
{
    REQUIRE(wUtils::Min(0.0, 1.0232434253) == 0.0);
    REQUIRE(wUtils::Min(0.247, 239088.2) == 0.247);
    REQUIRE(wUtils::Min(10.01, 10.001) == 10.001);
    REQUIRE(wUtils::Min(142930.0, 142931.0) == 142930.0);
    REQUIRE(wUtils::Min(-0.0, 1.0232434253) == 0.0);
    REQUIRE(wUtils::Min(-0.247, 239088.2) == -0.247);
    REQUIRE(wUtils::Min(-10.01, 10.001) == -10.01);
    REQUIRE(wUtils::Min(-142930.0, 142931.0) == -142930.0);
    REQUIRE(wUtils::Min(0.0, -1.0232434253) == -1.0232434253);
    REQUIRE(wUtils::Min(0.247, -239088.2) == -239088.2);
    REQUIRE(wUtils::Min(10.01, -10.001) == -10.001);
    REQUIRE(wUtils::Min(142930.0, -142931.0) == -142931.0);
    REQUIRE(wUtils::Min(-0.0, -1.0232434253) == -1.0232434253);
    REQUIRE(wUtils::Min(-0.247, -239088.2) == -239088.2);
    REQUIRE(wUtils::Min(-10.01, -10.001) == -10.01);
    REQUIRE(wUtils::Min(-142930.0, -142931.0) == -142931.0);
}