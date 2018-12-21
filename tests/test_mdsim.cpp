#include <catch.hpp>

#include "mdsim.h"

TEST_CASE("Particle instantiation") {
  Particle p;
  p.SetRadius(4);
  REQUIRE(p.GetRadius() == 4);
}
TEST_CASE("RNG vectors") {
  RNG rng;
  rng.Init(rand(), rand(), rand(), rand());
  double vec[3] = {0,0,0};
  rng.RandomUnitVector(3, vec);
  REQUIRE(abs(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] - 1.0) < 1e-12);
  rng.RandomUnitVector(2, vec);
  REQUIRE(abs(vec[0]*vec[0] + vec[1]*vec[1] - 1.0) < 1e-12);
  rng.RandomUniformVector(3, vec);
  REQUIRE(abs(vec[0]) < 0.5);
  REQUIRE(abs(vec[1]) < 0.5);
}
