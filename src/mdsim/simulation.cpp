#include "simulation.h"


void Simulation::Init(parameters * params) {
  params_ = params;
  space_.Init(params_);
  InitParticles();
}

void Simulation::InitParticles() {
  particles_.resize(params_->n_particles);
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    /* Initialize particle positions */
    it->Init(params_->n_dim, params_->delta);

    /* Update periodic boundary conditions */
    double ds[3];
    space_.PeriodicBCs(it->GetPosition(), ds);
    it->SetScaledPosition(ds);
  }
}

void Simulation::Run() {
  std::cout << "Beginning simulation\n";
  for (int i = 0; i < params_->n_steps; ++i) {
    UpdateParticlePositions();
  }
  std::cout << "Simulation complete\n";
  std::cout << "Particles reporting\n";
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    it->GetStatus();
  }

}

void Simulation::UpdateParticlePositions() {
  for (auto it = particles_.begin(); it != particles_.end(); ++it) {
    /* TODO Calculate forces */

    /* Update particle positions */
    it->UpdatePosition();

    /* Update periodic boundary conditions */
    double ds[3];
    space_.PeriodicBCs(it->GetPosition(), ds);
    it->SetScaledPosition(ds);
  }
}


