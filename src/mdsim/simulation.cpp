#include "simulation.h"


void Simulation::Init(parameters * params) {
  params_ = params;
  n_particles_ = params_->n_particles;
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
    double ds[3];
    space_.PeriodicBCs((*it)->GetPosition(), ds);
    (*it)->SetScaledPosition(ds);
  }
}

void Simulation::Run() {
  std::cout << "Beginning simulation\n";
  for (int i = 0; i < params_->n_steps; ++i) {
    CalculateForces();
    UpdateParticlePositions();
  }
  std::cout << "Simulation complete\n";
  std::cout << "Particles reporting\n";
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    (*it)->GetStatus();
  }
}

void Simulation::CalculateForces() { 
  /* Derived class should do something here */
}

void Simulation::UpdateParticlePositions() {
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    /* Update particle positions */
    (*it)->UpdatePosition();

    /* Update periodic boundary conditions */
    double ds[3];
    space_.PeriodicBCs((*it)->GetPosition(), ds);
    (*it)->SetScaledPosition(ds);
  }
}

