#ifndef _MDSIM_SIMULATION_H_
#define _MDSIM_SIMULATION_H_

#include <vector>
#include "parameters.h"
#include "particle.h"
#include "space.h"

class Simulation {
  protected:
    int n_particles_;

    std::vector<Particle*> particles_;
    parameters * params_;
    Space space_;

    virtual void InitParticles();
    virtual void CreateParticles();
    virtual void UpdateParticlePositions();
    virtual void CalculateForces();

  public:
    Simulation() {}
    virtual ~Simulation() {
      for (auto it=particles_.begin(); it!=particles_.end(); ++it) {
        delete (*it);
      }
      particles_.clear();
    }

    void Init(parameters * params);
    void Run();
};

#endif // _MDSIM_SIMULATION_H_
