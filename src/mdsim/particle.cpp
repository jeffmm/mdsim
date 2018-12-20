#include "mdsim.h"

void Particle::Init(int n_dim, double delta) {
  n_dim_ = n_dim;
  delta_ = delta;
  InitRandom();
}

void Particle::SetRadius(const double r) {
  rad_ = r;
}

void Particle::SetScaledPosition(const double sp[]) {
  for (int i=0; i<n_dim_; ++i) {
    spos_[i] = sp[i];
  }
}

void Particle::SetPosition(const double p[]) {
  for (int i=0; i<n_dim_; ++i) {
    pos_[i] = p[i];
  }
}

void Particle::SetVelocity(const double v[]) {
  for (int i=0; i<n_dim_; ++i) {
    vel_[i] = v[i];
  }
}

void Particle::InitRandom() {
  double dr[3] = {0,0,0};
  SetPosition(dr);
  double v[3] = {1,0,0};
  SetVelocity(v);
}

double Particle::GetVelocitySquared() {
  double v_mag2 = 0;
  for (int i=0; i<n_dim_; ++i) {
    v_mag2 += vel_[i]*vel_[i];
  }
  return v_mag2;
}

void Particle::GetStatus() {
  std::cout << "  Particle: \n"
            << "    Radius: " << rad_ << "\n"
            << "    Position: {" << pos_[0]
                        << " " << pos_[1]
                        << " " << pos_[2] <<"}\n"
            << "    Scaled Position: {" << spos_[0]
                        << " " << spos_[1]
                        << " " << spos_[2] <<"}\n"
            << "    Velocity: {" << vel_[0]
                        << " " << vel_[1]
                        << " " << vel_[2] <<"}\n";
}



/* Naive integrator */
void Particle::UpdatePosition() {
  for (int i = 0; i < n_dim_; ++i) {
    pos_[i] += vel_[i] * delta_;
  }
}
