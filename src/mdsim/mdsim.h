#ifndef _MDSIM_MAIN_H_
#define _MDSIM_MAIN_H_

#include "simulation.h"

class MDSim {
  private:
    Simulation sim_;
    parameters params_;
    void Init();
  public:
    MDSim();
    void SetParams(int n_dim, int n_periodic, int n_particles,
                   int n_steps, double box_size, double delta);
    void Run();
};

#endif // _MDSIM_MAIN_H_
