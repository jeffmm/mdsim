import os
import re
import sys
import platform
import subprocess

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
from shutil import copyfile, copymode
from distutils.version import LooseVersion


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following"
                "extensions: " + ", ".join(e.name for e in self.extensions)
            )

        if platform.system() == "Windows":
            cmake_version = LooseVersion(
                re.search(r"version\s*([\d.]+)", out.decode()).group(1)
            )
            if cmake_version < "3.1.0":
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=" + extdir,
            "-DPYTHON_EXECUTABLE=" + sys.executable,
        ]

        cfg = "Debug" if self.debug else "Release"
        build_args = ["--config", cfg]

        if platform.system() == "Windows":
            cmake_args += [
                "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}".format(cfg.upper(), extdir)
            ]
            if sys.maxsize > 2 ** 32:
                cmake_args += ["-A", "x64"]
            build_args += ["--", "/m"]
        else:
            cmake_args += ["-DCMAKE_BUILD_TYPE=" + cfg]
            build_args += ["--", "-j4"]

        env = os.environ.copy()
        env["CXXFLAGS"] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get("CXXFLAGS", ""), self.distribution.get_version()
        )
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env
        )
        subprocess.check_call(
            ["cmake", "--build", "."] + build_args, cwd=self.build_temp
        )
        # Copy debug binaries to main directory
        # test_bin = os.path.join(self.build_temp, 'mdsim_test')
        debug_bin = os.path.join(self.build_temp, "mdsim_debug")
        # self.copy_test_file(test_bin)
        current_dir = os.path.dirname(os.path.abspath(__file__))
        dest_file = os.path.join(current_dir, os.path.basename(debug_bin))
        print("copying {} -> {}".format(debug_bin, dest_file))
        copyfile(debug_bin, dest_file)
        copymode(debug_bin, dest_file)
        print()  # Add empty line for nicer output

    def copy_test_file(self, src_file):
        """
        Copy ``src_file`` to `tests/bin` directory, ensuring parent directory
        exists. Messages like `creating directory /path/to/package` and
        `copying directory /src/path/to/package -> path/to/package` are
        displayed on standard output. Adapted from scikit-build.
        """
        # Create directory if needed
        dest_dir = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), "tests", "bin"
        )
        if dest_dir != "" and not os.path.exists(dest_dir):
            print("creating directory {}".format(dest_dir))
            os.makedirs(dest_dir)

        # Copy file
        dest_file = os.path.join(dest_dir, os.path.basename(src_file))
        print("copying {} -> {}".format(src_file, dest_file))
        copyfile(src_file, dest_file)
        copymode(src_file, dest_file)


setup(
    name="mdsimcpp",
    version="0.0.1",
    author="Jeffrey M Moore",
    author_email="moore.jeffrey.m@gmail.com",
    description="A test project using python and C++ with pybind11",
    long_description="",
    packages=find_packages("mdsim/simulation"),
    package_dir={"": "mdsim/simulation"},
    ext_modules=[CMakeExtension("mdsim/simulation")],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)
