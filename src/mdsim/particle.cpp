#include "particle.h"

void Particle::Init(parameters * params) {
  params_ = params;
  n_dim_ = params_->n_dim;
  delta_ = params_->delta;
  //rng_.Init(params_->seed);
  //params_->seed = gsl_rng_get(rng_.r);
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
  //rng_.RandomUniformVector(n_dim_,pos_);
  //for (int i=0; i<n_dim_; ++i) {
    //pos_[i] = pos_[i] * params_->box_size;
  //}
  //rng_.RandomUnitVector(n_dim_, vel_);
  //for (int i=0; i<n_dim_; ++i) {
    //vel_[i] = vel_[i] * params_->velocity;
  //}
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
