#include "mdsim.h"

int main() {
  MDSim sim;
  long seed = 7777777;
  int ndim = 2;
  int nper = 2;
  int npart = 100;
  int nstep = 1000;
  double box = 100;
  double delta = 0.1;
  double noise = 0.1;
  double velocity = 10;
  double cutoff = 3;
  int sample = 10;
  parameters params(seed, ndim, nper, npart, nstep, box, 
      delta, noise, velocity, cutoff, sample);
  sim.SetParams(params);
  sim.Run();
}
