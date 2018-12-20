#include "mdsim.h"

MDSim::MDSim() {}

void MDSim::Init() {
  sim_.Init(&params_);
}

/* TODO Figure out a better way to do this using the Python interface */
void MDSim::SetParams(int n_dim, int n_periodic, int n_particles,
                      int n_steps, double box_size, double delta) {
  params_.n_dim = n_dim;
  params_.n_periodic = n_periodic;
  params_.n_particles = n_particles;
  params_.n_steps = n_steps;
  params_.box_size = box_size;
  params_.delta = delta;
}

void MDSim::Run() {
  Init();
  sim_.Run();
}



