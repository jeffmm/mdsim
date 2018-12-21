#include "mdsim.h"

MDSim::MDSim() {}

void MDSim::Init() {
  sim_.Init(&params_);
}

/* TODO Figure out a better way to do this using the Python
 * interface */
void MDSim::SetParams(parameters params) {
  params_ = params;
}

void MDSim::Run() {
  Init();
  sim_.Run();
}

