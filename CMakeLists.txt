cmake_minimum_required(VERSION 2.8.12)
project(mdsim)

set(SOURCE_DIR "src/mdsim")
include_directories(${SOURCE_DIR})
set(SOURCES "${SOURCE_DIR}/main.cpp")

add_subdirectory(lib/pybind11)
pybind11_add_module(mdsim ${SOURCES} "${SOURCE_DIR}/bindings.cpp")

set(TEST_DIR "tests")
set(TESTS ${SOURCES}
  "${TEST_DIR}/test_main.cpp"
  "${TEST_DIR}/test_mdsim.cpp")

include_directories(lib/Catch2/single_include/catch2)
add_executable("${PROJECT_NAME}_test" ${TESTS})
