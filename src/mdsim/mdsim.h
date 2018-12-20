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
    void SetParams(parameters params);
    void Run();
};

#endif // _MDSIM_MAIN_H_
