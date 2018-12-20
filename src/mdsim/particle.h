#ifndef _MDSIM_PARTICLE_H_
#define _MDSIM_PARTICLE_H_

typedef double double3[3];

#include <iostream> 
#include "parameters.h"
#include "rng.h"

class Particle {
  private:
    int n_dim_ = 3;
    double pos_[3],
           spos_[3],
           vel_[3],
           rad_ = 1,
           delta_ = 0.001;

    //RNG rng_;
    parameters * params_;
    void InitRandom();

  public:
    Particle() {
      std::fill(pos_,pos_+3,0.0);
      std::fill(spos_,spos_+3,0.0);
      std::fill(vel_,vel_+3,0.0);
    }
    void Init(parameters * params);
    void SetRadius(double r);
    void SetPosition(const double p[]);
    void SetScaledPosition(const double sp[]);
    void SetVelocity(const double v[]);


    const double3& GetPosition() const { return pos_; }
    const double3& GetVelocity() const { return vel_; }
    const double3& GetScaledPosition() const { return spos_; }
    double GetVelocitySquared();
    const double GetRadius() const { return rad_; }
    void GetStatus();
    void UpdatePosition();
};

#endif // _MDSIM_PARTICLE_H_
