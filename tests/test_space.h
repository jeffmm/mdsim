
TEST_CASE("Space behavior") {

  parameters params;
  Space s;
  params.SetBoxSize(20);
  params.SetDim(3);
  params.SetPeriodic(3);
  s.Init(&params);
  const double pos[3] = {15, 0, 5};
  double spos[3] = {0, 0, 0};

  SECTION("Test periodic boundary conditions") {
    /* Box size of 20 means simulation space runs from [-10, 10] along each
     * dimension. Periodic subspace runs from [-0.5, 0.5] in scaled
     * coordinates. Correct behavior also relies on the matrix inversion
     * algebra in the namespace defined in space.cpp. */
    s.PeriodicBCs(pos, spos);
    REQUIRE((spos[0] == -0.25 && spos[1] == 0 && spos[2] == 0.25) == true);
  }

  SECTION("Test correct unit cell volume") {
    /* This relies on the matrix determinant algebra in the namespace defined
     * in space.cpp. */
    REQUIRE(s.GetVolume() == 8000);

    /* Now test again in 2D. */
    params.SetDim(2);
    params.SetPeriodic(2);
    s.Init(&params);
    REQUIRE(s.GetVolume() == 400);
  }
}
