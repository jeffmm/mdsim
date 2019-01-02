#ifndef _MDSIM_VICSEK_PARTICLE_H_
#define _MDSIM_VICSEK_PARTICLE_H_

#include "particle.h"

class VicsekParticle : public Particle {

  private:
    double noise_;
    void AddNoise();
    void UpdateDirector();

  public:
    VicsekParticle() : Particle() {}
    void SetNoise(const double n) { noise_ = n; }
    const double GetNoise() const { return noise_; }
    virtual void UpdatePosition();
};

#endif // _MDSIM_VICSEK_PARTICLE_H_
