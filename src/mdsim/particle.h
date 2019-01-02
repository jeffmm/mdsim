#ifndef _MDSIM_PARTICLE_H_
#define _MDSIM_PARTICLE_H_

typedef double double3[3];

#include <iostream> 
#include "parameters.h"
#include "rng.h"

class Particle {
  protected:
    int n_dim_ = 3,
        n_interactors_ = 0;
    double pos_[3],
           spos_[3],
           dir_[3],
           vel_[3],
           force_[3],
           rad_ = 1,
           delta_ = 0.001;

    RNG rng_;
    parameters * params_;
    virtual void InitRandom();

  public:
    Particle() {
      std::fill(pos_, pos_+3, 0.0);
      std::fill(spos_, spos_+3, 0.0);
      std::fill(dir_, dir_+3, 0.0);
      std::fill(vel_, vel_+3, 0.0);
      std::fill(force_, force_+3, 0.0);
    }
    virtual ~Particle() {}
    void Init(parameters * params);
    void SetRadius(const double r) { rad_ = r; }
    void SetPosition(const double p[]);
    void SetScaledPosition(const double sp[]);
    void SetVelocity(const double v[]);
    void SetDirector(const double d[]);
    void SetForce(const double f[]);
    void AddForce(const double f[]);
    void AddInteractor() { n_interactors_++; }
    void ZeroForces();

    const double3& GetPosition() const { return pos_; }
    const double3& GetVelocity() const { return vel_; }
    const double3& GetDirector() const { return dir_; }
    const double3& GetForce() const { return force_; }
    const double3& GetScaledPosition() const { return spos_; }
    double GetVelocitySquared();
    const double GetRadius() const { return rad_; }

    virtual void GetStatus();
    virtual void UpdatePosition();
    virtual void CalculateForces() {}
};

#endif // _MDSIM_PARTICLE_H_
