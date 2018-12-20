#include <catch.hpp>

#include "mdsim.h"

TEST_CASE("Particle instantiation") {
  Particle p(1,2,3,4);
  REQUIRE(p.getPositionX() == 1);
  REQUIRE(p.getPositionY() == 2);
  REQUIRE(p.getPositionZ() == 3);
  REQUIRE(p.getRadius() == 4);
}
