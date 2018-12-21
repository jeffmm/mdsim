import unittest
import mdsim.mdsim as md
import numpy as np

class MainTest(unittest.TestCase):
    def test_version(self):
        self.assertEqual(md.__version__,'0.0.1')
    def test_rng(self):
        rng = md.RNG()
        seed = np.random.randint(100000,9999999)
        rng.initCold(seed)
        N = 100000
        x = np.array([rng.randUniform() for i in range(N)])
        self.assertEqual(round(x.std()-np.sqrt(1/12), 1), 0)
        x = np.array([rng.randGaussian(0,1) for i in range(N)])
        self.assertEqual(round(x.std()-1,1), 0)
        x = np.array([rng.randInt() for i in range(N)])
        self.assertEqual(round(x.std()-10*np.sqrt(1/12), 1), 0)



if __name__ == '__main__':
    unittest.main()
