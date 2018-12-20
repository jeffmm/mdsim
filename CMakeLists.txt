cmake_minimum_required(VERSION 2.8.12)
project(mdsim)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


set(SOURCE_DIR "src/mdsim")
#include_directories(${SOURCE_DIR})

find_package(GSL REQUIRED)
include_directories(${SOURCE_DIR} ${GSL_INCLUDE_DIRS})


set(SOURCES "${SOURCE_DIR}/mdsim.cpp"
            "${SOURCE_DIR}/particle.cpp"
            "${SOURCE_DIR}/space.cpp"
            "${SOURCE_DIR}/simulation.cpp")
            #"${GSL_INCLUDE_DIRS}/gsl/gsl_rng.h"
            #"${GSL_INCLUDE_DIRS}/gsl/gsl_randist.h")

link_directories(${GSL_ROOT_DIR}/lib)

add_subdirectory(lib/pybind11)
pybind11_add_module(mdsim ${SOURCES} "${SOURCE_DIR}/bindings.cpp")
#target_include_directories(mdsim PRIVATE ${SOURCE_DIR} ${GSL_INCLUDE_DIRS})
target_link_libraries(mdsim PRIVATE GSL::gsl)

set(TEST_DIR "tests")
set(TESTS ${SOURCES}
  "${TEST_DIR}/test_main.cpp"
  "${TEST_DIR}/test_mdsim.cpp")

include_directories(lib/Catch2/single_include/catch2)
add_executable("${PROJECT_NAME}_test" ${TESTS})
