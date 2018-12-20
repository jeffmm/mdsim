#ifndef _MDSIM_SIMULATION_H_
#define _MDSIM_SIMULATION_H_

#include <vector>
#include "parameters.h"
#include "particle.h"
#include "space.h"

class Simulation {
  private:
    std::vector<Particle> particles_;
    parameters * params_;
    Space space_;

    void InitParticles();
    void UpdateParticlePositions();
  public:
    Simulation() {}
    void Init(parameters * params);
    void Run();

};

#endif // _MDSIM_SIMULATION_H_
