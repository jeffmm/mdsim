#include "mdsim.h"

Particle::Particle(double x1, double x2, double x3, double r) {
  setRadius(r);
  setPosition(x1, x2, x3);
}
void Particle::setRadius(double r) {
  rad_ = (double) r;
}
void Particle::setPosition(double x1, double x2, double x3) {
  pos_[0] = x1;
  pos_[1] = x2;
  pos_[2] = x3;
}
double const Particle::getRadius() const { return rad_; }
double const Particle::getPositionX() const { return pos_[0]; }
double const Particle::getPositionY() const { return pos_[1]; }
double const Particle::getPositionZ() const { return pos_[2]; }

void Particle::getStatus() {
  std::cout << "Particle: \n"
            << "  Radius: " << rad_ << "\n"
            << "  Position: {" << pos_[0]
                        << " " << pos_[1]
                        << " " << pos_[2] <<"}\n";
}

