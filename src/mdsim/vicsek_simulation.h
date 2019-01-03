#ifndef _MDSIM_VICSEK_SIMULATION_H_
#define _MDSIM_VICSEK_SIMULATION_H_

#include "simulation.h"
#include "vicsek_particle.h"
#include <fstream>

class VicsekSimulation : public Simulation {
  private:
    /* Nothing special: just a simulation with VicsekParticles */
    std::fstream gpo_file_;
    virtual void CreateParticles();
    virtual void CalculateForces();
    virtual void RunAnalysis();
    virtual void InitAnalysis();
    virtual void FinalAnalysis();
    void CalculateGlobalPolarOrder();
  public:
    VicsekSimulation() : Simulation() {}
};

#endif // _MDSIM_VICSEK_SIMULATION_H_
