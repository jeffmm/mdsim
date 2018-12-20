#include <catch.hpp>

#include "mdsim.h"

TEST_CASE("Particle instantiation") {
  Particle p;
  p.SetRadius(4);
  REQUIRE(p.GetRadius() == 4);
}
