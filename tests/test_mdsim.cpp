#include <catch.hpp>

#include "mdsim.h"

TEST_CASE("Addition and subtraction") {
  REQUIRE(add(1, 1) == 2);
  REQUIRE(subtract(2, 3) == -1);
}
