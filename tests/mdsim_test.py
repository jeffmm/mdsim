import unittest
import mdsim.mdsim as md

class MainTest(unittest.TestCase):
    def test_version(self):
        self.assertEqual(md.__version__,'0.0.1')

if __name__ == '__main__':
    unittest.main()
