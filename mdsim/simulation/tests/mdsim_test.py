import mdsim as md
import numpy as np


def test_version():
    assert md.__version__ == "0.0.1", "mdsim version does not match expected value!"


def assert_equal(a, b):
    assert a == b, "Assertion failed in mdsim_test.py!"


def test_rng():
    # These tests are statistical in nature, and it is possible they can
    # fail, however it is very unlikely.
    rng = md.RNG()
    # Warm up the RNG from a single long integer
    seed = np.random.randint(100000, 9999999999)
    rng.initCold(seed)
    # Number of random numbers to generate for statistics. Error should
    # scale as 1/sqrt(N), so select a large N and check that statistical
    # variances match expected theoretical variances for given distribution
    # (out to the tenths decimal place).
    N = 100000
    # Check uniform distribution matches expected variance V=1/12
    x = np.array([rng.randUniform() for i in range(N)])
    assert_equal(round(x.std() - np.sqrt(1 / 12), 1), 0)
    # Check Gaussian distribution matches expected variance V=sigma^2
    x = np.array([rng.randGaussian(0, 1) for i in range(N)])
    assert_equal(round(x.std() - 1, 1), 0)
    # Check that uniform int dist matches expected variance V=100/12
    x = np.array([rng.randInt() for i in range(N)])
    assert_equal(round(x.std() - 10 * np.sqrt(1 / 12), 1), 0)
