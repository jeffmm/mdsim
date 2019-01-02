#ifndef _MDSIM_VICSEK_SIMULATION_H_
#define _MDSIM_VICSEK_SIMULATION_H_

#include "simulation.h"
#include "vicsek_particle.h"

class VicsekSimulation : public Simulation {
  private:
    /* Nothing special: just a simulation with VicsekParticles */
    virtual void CreateParticles();
    virtual void CalculateForces();
  public:
    VicsekSimulation() : Simulation() {}
};

#endif // _MDSIM_VICSEK_SIMULATION_H_
