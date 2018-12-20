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

    //py::class_<Particle>(m, "Particle")
        //.def(py::init<const double, const double, const double, const double>())
        //.def("setRadius", &Particle::setRadius)
        //.def("setPositionX", &Particle::setPosition)
        //.def("getRadius", &Particle::getRadius)
        //.def("getPositionX", &Particle::getPositionX)
        //.def("getPositionY", &Particle::getPositionY)
        //.def("getPositionZ", &Particle::getPositionZ)
        //.def("getStatus", &Particle::getStatus);
    py::class_<parameters>(m, "Params")
      .def(py::init<>());

    py::class_<MDSim>(m, "Sim")
      .def(py::init<>())
      .def("setParams", &MDSim::SetParams)
      .def("run", &MDSim::Run);


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
