#ifndef _MDSIM_SPACE_H_
#define _MDSIM_SPACE_H_

#include "parameters.h"
#include <math.h>
#include <algorithm>

class Space {
  private:
    int n_dim_,
        n_periodic_;
    double box_size_,
           volume_,
           uc_[9], // unit cell matrix
           uc_inv_[9], // inverse unit cell matrix
           a_[9], // direct lattice vector
           b_[9], // reciprocal lattice vector
           a_perp_[3]; // perp distance between opposite unit cell faces

    void CalculateUnitCell();
  public:
    Space();
    void PeriodicBCs(const double r[], double s[]);
    void Init(parameters * params);
    const double GetVolume() const { return volume_; }
};

#endif // _MDSIM_SPACE_H_
