#include "mdsim.h"

int main() {

  MDSim sim;
  parameters params(41589143, 2, 2, 100, 100, 100, 0.1, 0.1, 10, 5);
  sim.SetParams(params);
  sim.Run();

}
