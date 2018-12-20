#ifndef _MDSIM_RNG_H_
#define _MDSIM_RNG_H_

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>

class RNG { 
  private:
    const gsl_rng_type *T;
    void Clear() {
      gsl_rng_free(r);
    }
  public:
    gsl_rng *r;
    RNG() {}
    RNG(long seed) {
      Init(seed);
    }
    ~RNG() {
      Clear();
    }
    void Init(long seed) {
      gsl_rng_env_setup();
      T = gsl_rng_default;
      r = gsl_rng_alloc(T);
      gsl_rng_set(r, seed);
    }
    RNG(const RNG& that) {
      this->Init(gsl_rng_get(that.r));
    }
    RNG& operator=(RNG const&that) {
      this->Init(gsl_rng_get(that.r));
      return *this;
    }
    void RandomUnitVector(int n_dim, double vec[]) {
      double x, y, z, w, t;

      w = 1.0;
      if (n_dim == 3) {
          z = 2.0 * gsl_rng_uniform_pos(r) - 1.0;
          w = sqrt(1 - z * z);
          vec[2] = z;
      }

      t = 2.0 * M_PI * gsl_rng_uniform_pos(r);
      x = w * cos(t);
      y = w * sin(t);
      vec[0] = x;
      vec[1] = y;
    }
    void RandomUniformVector(int n_dim, double vec[]) {
      for (int i=0; i<n_dim; ++i) {
        vec[i] = gsl_rng_uniform_pos(r) - 0.5;
      }
    }
};

#endif // _MDSIM_RNG_H_
