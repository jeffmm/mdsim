#ifndef _MDSIM_PARAMETERS_H_
#define _MDSIM_PARAMETERS_H_

struct parameters {
  int n_dim = 3;
  int n_periodic = 3;
  int n_particles = 10;
  int n_steps = 10000;
  double box_size = 100;
  double delta = 0.001;
};


#endif // _MDSIM_PARAMETERS_H_
