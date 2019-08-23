#include "vicsek_simulation.h"

void VicsekSimulation::CreateParticles() {
  for (int i=0; i<params_->n_particles; ++i) {
    particles_.push_back(new VicsekParticle);
  }
}

void VicsekSimulation::CalculateForces() {
  /* For now, do all-pair interactions */
  for (int i=0; i<n_particles_-1; ++i) {
    for (int j=i+1; j<n_particles_; ++j) {
      double dr = space_.MinDistance(particles_[i]->GetPosition(), 
                              particles_[i]->GetScaledPosition(),
                              particles_[j]->GetPosition(),
                              particles_[j]->GetScaledPosition());
      if (dr < params_->cutoff) {
        /* If particles are within a cutoff, add the interacting particles'
         * directors to the particle's total force, so that we can add all
         * the directors together for the average. */
        particles_[i]->AddForce(particles_[j]->GetDirector());
        particles_[i]->AddInteractor();
        particles_[j]->AddForce(particles_[i]->GetDirector());
        particles_[j]->AddInteractor();
      }
    }
  }
}

void VicsekSimulation::RunAnalysis() {
  CalculateGlobalPolarOrder();
}

void VicsekSimulation::CalculateGlobalPolarOrder() {
  double3 gpo;
  std::fill(gpo, gpo+3, 0.0);
  for (auto it=particles_.begin(); it!=particles_.end(); ++it) {
    const double3& u = (*it)->GetDirector();
    for (int i=0; i<n_dim_; ++i) {
      gpo[i] += u[i];
    }
  }
  double gpo_mag = 0.0;
  for (int i=0; i<n_dim_; ++i) {
    gpo[i] /= n_particles_;
    gpo_mag += gpo[i]*gpo[i];
  }
  gpo_mag = sqrt(gpo_mag);
  gpo_file_ << gpo_mag << " ";
}

void VicsekSimulation::InitAnalysis() {
  std::string fname = "vicsek_global_polar_order.dat";
  gpo_file_.open(fname, std::ios::out);
}

void VicsekSimulation::FinalAnalysis() {
  if (gpo_file_.is_open()) {
    gpo_file_.close();
  }
}
