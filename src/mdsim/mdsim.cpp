#include "mdsim.h"

/* TODO Figure out a better way to do this using the Python
 * interface */
void MDSim::SetParams(parameters params) {
  params_ = params;
}

void MDSim::Run() {
  sim_.Init(&params_);
  sim_.Run();
}

