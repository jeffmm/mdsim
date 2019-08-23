#ifndef _MDSIM_MAIN_H_
#define _MDSIM_MAIN_H_

#include "vicsek_simulation.h"

class MDSim {
  private:
    VicsekSimulation sim_;
    parameters params_;
  public:
    MDSim() {}
    void SetParams(parameters params);
    void Run();
};


#endif // _MDSIM_MAIN_H_
