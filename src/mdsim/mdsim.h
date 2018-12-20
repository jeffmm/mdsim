#ifndef _MDSIM_PARTICLE_H_
#define _MDSIM_PARTICLE_H_

#include <iostream>

class Particle {
  private:
    double pos_[3],
           rad_;
  public:
    Particle(double x1, double x2, double x3, double r);
    void setRadius(double r);
    void setPosition(double x1, double x2, double x3);
    double const getRadius() const;
    double const getPositionX() const;
    double const getPositionY() const;
    double const getPositionZ() const;
    void getStatus();
};

#endif // _MDSIM_PARTICLE_H_
