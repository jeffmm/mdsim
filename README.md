# MDSim

MDSim is a Python module written in C++ that uses CMake to compile the module and run C++ and Python unit tests. The module was written for learning purposes only, and it runs a simple 
[Vicsek model](https://en.wikipedia.org/wiki/Vicsek_model) simulation.

## Installation

Make sure the repo is installed with all submodules:

```
git clone --recursive https://github.com/jeffmm/mdsim.git
```

Make sure that there is a detectable C++11 compatible compiler installed and run

```
pip3 install .
```

If install is successful, you can import the module straight away in Python:

```
from mdsim import mdsim
p = mdsim.Params()
s = mdsim.Simulation()
s.runSimulation(p)
```

## Development

To build the library, simply run

```
python3 setup.py build
```
## C++/Python bindings

The C++/Python bindings were written using the header-only [pybind11 library](https://github.com/pybind/). Functions are exposed in the Python module with by the code written in *src/mdsim/bindings.cpp*. The installation of the submodule is written in the CMakeLists.txt file.

See https://github.com/pybind/cmake_example for more info.

## Unit tests

To run unit tests, do

```
python3 setup.py test
```
Unit tests are written in the *test* directory in both python and C++. The header-only [Catch2 library](https://github.com/catchorg/Catch2) was used for C++ unit tests.

