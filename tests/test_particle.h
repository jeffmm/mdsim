
TEST_CASE("Particle behavior") {

  parameters params;
  Particle p;
  params.SetSeed(rand());

  SECTION("Particle initialization") {
    /* First check particle defaults */
    const double3 &pos = p.GetPosition();
    const double3 &vel = p.GetVelocity();
    const double3 &spos = p.GetScaledPosition();
    REQUIRE((pos[0] == 0 && pos[1] == 0 && pos[2] == 0) == true);
    REQUIRE((vel[0] == 0 && vel[1] == 0 && vel[2] == 0) == true);
    REQUIRE((spos[0] == 0 && spos[1] == 0 && spos[2] == 0) == true);
    REQUIRE(p.GetRadius() == 1);

    /* Now check for correct initialization */
    p.Init(&params);
    const double3 &init_pos = p.GetPosition();
    double halfbox = 0.5*params.box_size;
    REQUIRE((abs(init_pos[0]) < halfbox && abs(init_pos[1]) < halfbox 
          && abs(init_pos[2]) < halfbox) == true);
    double v = params.velocity;
    REQUIRE((p.GetVelocitySquared() - v*v) < 1e-12);
  }

  SECTION("Particle constant getter/setter functions") {
    p.SetRadius(5);
    REQUIRE(p.GetRadius() == 5);
  }

  SECTION("Particle vector getter/setter functions 2D") {
    /* Explicitly set particle dimensionality to 2 */
    params.SetDim(2);
    p.Init(&params);
    double v[3] = {1,1,1};
    p.SetPosition(v);
    p.SetScaledPosition(v);
    p.SetVelocity(v);
    const double3& pos = p.GetPosition();
    const double3& spos = p.GetScaledPosition();
    const double3& vel = p.GetVelocity();
    /* The particle's third dimension should remain untouched */
    REQUIRE((pos[0] == 1 && pos[1] == 1 && pos[2] == 0) == true);
    REQUIRE((spos[0] == 1 && spos[1] == 1 && spos[2] == 0) == true);
    REQUIRE((vel[0] == 1 && vel[1] == 1 && vel[2] == 0) == true);
    REQUIRE(p.GetVelocitySquared() == 2);
  }

  SECTION("Particle vector getter/setter functions 3D") {
    /* Explicitly set particle dimensionality to 3 */
    params.SetDim(3);
    p.Init(&params);
    double v[3] = {1,1,1};
    p.SetPosition(v);
    p.SetScaledPosition(v);
    p.SetVelocity(v);
    const double3& pos = p.GetPosition();
    const double3& spos = p.GetScaledPosition();
    const double3& vel = p.GetVelocity();
    REQUIRE((pos[0] == 1 && pos[1] == 1 && pos[2] == 1) == true);
    REQUIRE((spos[0] == 1 && spos[1] == 1 && spos[2] == 1) == true);
    REQUIRE((vel[0] == 1 && vel[1] == 1 && vel[2] == 1) == true);
    REQUIRE(p.GetVelocitySquared() == 3);
  }

  /* Move particle one step in the direction of the velocity */
  SECTION("Particle position update") {
    params.SetDim(3);
    params.SetDelta(1);
    p.Init(&params);
    double vel[3] = {1,1,1};
    double pos[3] = {0,0,0};
    p.SetPosition(pos);
    p.SetVelocity(vel);
    /* Move the particle by one step along the velocity vector */
    p.UpdatePosition();
    const double3& new_pos = p.GetPosition();
    /* New particle position should equal the velocity (since delta=1) */
    REQUIRE((new_pos[0] == 1 && new_pos[1] == 1 && new_pos[2] == 1) == true);
  }
}


