#ifndef _MDSIM_PARAMETERS_H_
#define _MDSIM_PARAMETERS_H_

struct parameters {
  int n_dim = 3;
  int n_periodic = 3;
  int n_particles = 10;
  int n_steps = 10000;
  double box_size = 100;
  double delta = 0.001;
  double noise = 0.2;
  double velocity = 10;
  double cutoff = 3;
  long seed = 7777777;
  parameters(long sd=7777777, int ndim=3, int nper=3, 
             int npart=10, int nstep=1000, double bs=100, 
             double dlt=0.001, double ns=0.2, double vel=10,
             double cut=3) {
    seed = sd;
    n_dim = ndim;
    n_periodic = nper;
    n_particles = npart;
    n_steps = nstep;
    box_size = bs;
    delta = dlt;
    noise = ns;
    velocity = vel;
    cutoff = cut;
  }
  void SetSeed(int val) { seed = val; }
  void SetDim(int val) { n_dim = val; }
  void SetPeriodic(int val) { n_periodic = val; }
  void SetNumParticles(int val) { n_particles = val; }
  void SetNumSteps(int val) { n_steps = val; }
  void SetBoxSize(double val) { box_size = val; }
  void SetDelta(double val) { delta = val; }
  void SetNoise(double val) { noise = val; }
  void SetVelocity(double val) { velocity = val; }
  void SetCutoff(double val) { cutoff = val; }
};


#endif // _MDSIM_PARAMETERS_H_
