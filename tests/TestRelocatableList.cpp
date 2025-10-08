#include <catch2/catch_all.hpp>
#include "TungstenUtils/RelocatableList.hpp"

TEST_CASE("Add and Remove Integers", "[RelocatableList]")
{
    wUtils::RelocatableList<int32_t> relocatableList;

    REQUIRE(relocatableList.Count() == 0);
}