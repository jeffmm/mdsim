#include "vicsek_particle.h"

/* Add random noise from uniform distribution in range [-noise, noise) to
 * orientation angles defined by the particle director. */

void VicsekParticle::AddNoise() {
  /* Get 2D theta angle associated with director */
  double theta = atan2(dir_[1],dir_[0]);
  /* Add random noise to theta */
  theta += (2*rng_.RandomUniform()-1)*noise_;
  double phi = M_PI/2;
  /* If in three dimensions, adjust phi as well */
  if (n_dim_ == 3) {
    phi = atan2(sqrt(dir_[0]*dir_[0]+dir_[1]*dir_[1]), dir_[2]);
    /* Add random noise to phi */
    phi += (2*rng_.RandomUniform()-1)*noise_;
  }
  /* Update director */
  dir_[0] = sin(phi)*cos(theta);
  dir_[1] = sin(phi)*sin(theta);
  dir_[2] = cos(phi);

  /* Since velocity is constant for Vicsek model, simply update here */
  for (int i=0; i<n_dim_; ++i) {
    vel_[i] = dir_[i] * params_->velocity;
  }
}

void VicsekParticle::UpdateDirector() {
  double dir_mag = 0;
  /* The force vector contains the sum of directors for interacting
     Vicsek particles within a distance cutoff. The new director
     should be an average of those directors and itself */
  for (int i=0; i<n_dim_; ++i) {
    dir_[i] += force_[i];
    dir_mag += dir_[i]*dir_[i];
  }
  /* Normalize unit vector */
  dir_mag = sqrt(dir_mag);
  for (int i=0; i<n_dim_; ++i) {
    dir_[i] /= dir_mag;
  }
}

void VicsekParticle::UpdatePosition() {
  UpdateDirector();
  AddNoise();
  for (int i = 0; i < n_dim_; ++i) {
    pos_[i] += vel_[i] * delta_;
  }
}


