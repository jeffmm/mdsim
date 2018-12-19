import unittest
import mdsim.mdsim as md

class MainTest(unittest.TestCase):
    def test_add(self):
        self.assertEqual(md.add(1, 2), 3)
    def test_subtract(self):
        self.assertEqual(md.subtract(1, 2),-1)
    def test_version(self):
        self.assertEqual(md.__version__,'0.0.1')


if __name__ == '__main__':
    unittest.main()
