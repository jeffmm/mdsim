#include "space.h"

namespace {
  int nint(double x) {
    return (x < 0.0 ? (int) (x - 0.5) : (int) (x + 0.5));
  }

  double determinant2D(double uc[]) {
    double d = uc[0]*uc[3] - uc[2]*uc[1];
    return d;
  }

  double determinant3D(double uc[]) {
    double d = uc[0] * (uc[4]*uc[8] - uc[7]*uc[5]) 
             - uc[1] * (uc[3]*uc[8] - uc[6]*uc[5]) 
             + uc[2] * (uc[3]*uc[7] - uc[6]*uc[4]);
    return d;
  }

  //Inverts symmetric "linear" 2D matrix
  void invert_sym_2d_matrix(double a[], double b[]) {
      double inv_det;
      inv_det = a[0]*a[3] - a[1]*a[1];
      inv_det = 1.0 / inv_det;
      b[0] = a[3] * inv_det;
      b[3] = a[0] * inv_det;
      b[2] = b[1] = -a[1] * inv_det;
  }

  //Inverts symmetric "linear" 3D matrix
  void invert_sym_3d_matrix(double a[], double b[]) {
      double inv_det;
      inv_det = a[0] * (a[4]*a[8] - a[5]*a[7])
          - a[1] * (a[3]*a[8] - a[5]*a[6])
          + a[2] * (a[3]*a[7] - a[4]*a[6]);
      inv_det = 1.0/inv_det;
      b[0] = inv_det * (a[4]*a[8] - a[5]*a[7]);
      b[4] = inv_det * (a[0]*a[8] - a[2]*a[6]);
      b[8] = inv_det * (a[0]*a[4] - a[1]*a[3]);
      b[1] = b[3] = -inv_det * (a[3]*a[8] - a[5]*a[6]);
      b[2] = b[6] = inv_det * (a[3]*a[7] - a[4]*a[6]);
      b[5] = b[7] = -inv_det * (a[0]*a[7] - a[1]*a[6]);
  }
} // namespace

Space::Space() {
  std::fill(uc_, uc_+9, 0.0);
  std::fill(uc_inv_, uc_inv_+9, 0.0);
  std::fill(a_, a_+9, 0.0);
  std::fill(b_, b_+9, 0.0);
  std::fill(a_perp_, a_perp_+3, 0.0);
}

void Space::Init(parameters * params) {
  n_dim_ = params->n_dim;
  n_periodic_ = params->n_periodic;
  box_size_ = params->box_size;

  // No skewed unit cells for now
  for (int i=0; i<n_dim_; ++i) {
    for (int j=0; j<n_dim_; ++j) {
      uc_[i*n_dim_+j] = (i==j ? 1 : 0) * box_size_;
    }
  }
  CalculateUnitCell();
}

void Space::PeriodicBCs(const double r[], double s[]) {
  for (int i = 0; i < n_periodic_; ++i) {
    s[i] = 0.0;
    for (int j = 0; j < n_periodic_; ++j) {
      s[i] += uc_inv_[n_dim_*i+j] * r[j];
    }
    s[i] -= nint(s[i]);
  }
}

void Space::CalculateUnitCell() {
  /* Calculate unit cell volume, which is determinant of unit cell, and
     compute inverse unit cell matrix. */
  if (n_dim_==2) {
    volume_ = determinant2D(uc_);
    invert_sym_2d_matrix(uc_, uc_inv_);
  }
  else if (n_dim_==3) {
    volume_ = determinant3D(uc_);
    invert_sym_3d_matrix(uc_, uc_inv_);
  }

  /* Set up direct and reciprocal lattice vectors. */
  for (int i = 0; i < n_dim_; ++i)
    for (int j = 0; j < n_dim_; ++j) {
      a_[n_dim_*i+j] = uc_[n_dim_*j+i];
      b_[n_dim_*i+j] = uc_inv_[n_dim_*i+j];
    }

  /* Compute perpendicular distances between opposite unit cell faces. */
  for (int i = 0; i < n_dim_; ++i) {
    double b_mag2 = 0.0;
    for (int j = 0; j < n_dim_; ++j)
      b_mag2 += (b_[n_dim_*i+j]*b_[n_dim_*i+j]);
    double b_mag = sqrt(b_mag2);
    a_perp_[i] = 1.0 / b_mag;
  }
}


