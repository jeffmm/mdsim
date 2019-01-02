#include <pybind11/pybind11.h>
#include "mdsim.h"

namespace py = pybind11;

PYBIND11_MODULE(mdsim, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

        Params
        Sim
    )pbdoc";
    py::class_<RNG>(m, "RNG")
        .def(py::init<>())
        .def("initCold", &RNG::InitCold)
        .def("init", &RNG::Init)
        .def("randUniform", &RNG::RandomUniform)
        .def("randUniformDbl", &RNG::RandomUniformDbl)
        .def("randInt", &RNG::RandInt)
        .def("randGaussian", &RNG::RandomGaussian)
        .def("randUnitVector", &RNG::RandomUnitVector)
        .def("randUniformVector", &RNG::RandomUniformVector);

    py::class_<parameters>(m, "Params", R"pbdoc(
        Simulation parameters for MDSim.

        Can initialize with n_dim, n_periodic,
        n_particles, n_steps, box_size, delta, noise, velocity, and cutoff
        (int, int, int, int, float, float, float, float, float).

        Defaults are:
          n_dim = 3
          n_periodic = 3
          n_particles = 10
          n_steps = 1000
          box_size = 100
          delta = 0.001
          noise = 0.2
          velocity = 10
          cutoff = 3

        Use setter functions to change parameters
        from defaults:
          setDim(int)
          setPeriodic(int)
          setNumParticles(int)
          setNumSteps(int)
          setBoxSize(float)
          setDelta(float)
          setNoise(float)
          setVelocity(float)
          setCutoff(float)
    )pbdoc")
      .def(py::init<long,int,int,int,int,double,double,double,double,double>(),
          py::arg("sd")=777777,
          py::arg("ndim")=3, py::arg("nper")=3,
          py::arg("npart")=10, py::arg("nstep")=1000,
          py::arg("bs")=100, py::arg("dlt")=0.001,
          py::arg("ns")=0.2, py::arg("vel")=10,
          py::arg("cut")=3)
      .def("setSeed",&parameters::SetSeed)
      .def("setDim",&parameters::SetDim)
      .def("setPeriodic",&parameters::SetPeriodic)
      .def("setNumParticles",&parameters::SetNumParticles)
      .def("setNumSteps",&parameters::SetNumSteps)
      .def("setBoxSize",&parameters::SetBoxSize)
      .def("setDelta",&parameters::SetDelta)
      .def("setNoise",&parameters::SetNoise)
      .def("setVelocity",&parameters::SetVelocity)
      .def("setCutoff",&parameters::SetCutoff);

    py::class_<MDSim>(m, "Sim", R"pbdoc(
        Simulation object for MDSim.

        Initialize the simulation parameters by passing
        a MDSim.Params object using the setParams() function.

        Run the simulation using the run() function.
    )pbdoc")
      .def(py::init<>())
      .def("setParams", &MDSim::SetParams,R"pbdoc(
        Set the simulation parameters.

        Takes a MDSim.Params object as an argument.

        See the MDSim.Params documentation for more details.
    )pbdoc")
      .def("runSimulation", &MDSim::Run,R"pbdoc(
        Run the simulation.
      )pbdoc");



#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
