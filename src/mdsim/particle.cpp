#include "particle.h"

void Particle::Init(parameters * params) {
  params_ = params;
  n_dim_ = params_->n_dim;
  delta_ = params_->delta;
  rng_.InitCold(params_->seed);
  params_->seed = (long) (1e4*rng_.JKISS()+rng_.JKISS());
  InitRandom();
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

void Particle::SetDirector(const double d[]) {
  for (int i=0; i<n_dim_; ++i) {
    dir_[i] = d[i];
  }
}

void Particle::SetForce(const double f[]) {
  for (int i=0; i<n_dim_; ++i) {
    force_[i] = f[i];
  }
}

void Particle::AddForce(const double f[]) {
  for (int i=0; i<n_dim_; ++i) {
    force_[i] += f[i];
  }
}

void Particle::ZeroForces() {
  std::fill(force_, force_+3, 0.0);
  n_interactors_ = 0;
}

void Particle::InitRandom() {
  /* Initialize random position within system box */
  rng_.RandomUniformVector(n_dim_,pos_);
  for (int i=0; i<n_dim_; ++i) {
    pos_[i] = pos_[i] * params_->box_size;
  }
  /* Initialize random orientation */
  rng_.RandomUnitVector(n_dim_, dir_);
  /* Initialize particle velocity along orientation */
  for (int i=0; i<n_dim_; ++i) {
    vel_[i] = dir_[i] * params_->velocity;
  }
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
