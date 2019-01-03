#include "simulation.h"


void Simulation::Init(parameters * params) {
  params_ = params;
  n_particles_ = params_->n_particles;
  n_dim_ = params_->n_dim;
  space_.Init(params_);
  CreateParticles();
  InitParticles();
}

void Simulation::CreateParticles() {
  for (int i=0; i<n_particles_; ++i) {
    particles_.push_back(new Particle);
  }
}

void Simulation::InitParticles() {
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    /* Initialize particle positions */
    (*it)->Init(params_);

    /* Update periodic boundary conditions */
    double ds[3] = {0,0,0};
    space_.PeriodicBCs((*it)->GetPosition(), ds);
    (*it)->SetScaledPosition(ds);
  }
}

void Simulation::Run() {
  InitAnalysis();
  for (int i = 0; i < params_->n_steps; ++i) {
    CalculateForces();
    UpdateParticlePositions();
    /* Just do analyses every 100 steps for now */
    if (i%100 == 0) {
      RunAnalysis();
    }
  }
  FinalAnalysis();
}

void Simulation::CalculateForces() { 
  /* Derived class should do something here */
}

void Simulation::UpdateParticlePositions() {
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    /* Update particle positions */
    (*it)->UpdatePosition();

    /* Update periodic boundary conditions */
    double ds[3] = {0,0,0};
    space_.PeriodicBCs((*it)->GetPosition(), ds);
    (*it)->SetScaledPosition(ds);
  }
}

