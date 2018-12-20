import unittest
import mdsim.mdsim as md

class MainTest(unittest.TestCase):
    def test_version(self):
        self.assertEqual(md.__version__,'0.0.1')
    def test_particle(self):
        p = md.Particle(0, 1, 2, 3)
        self.assertEqual(p.getRadius(), 3)
        self.assertEqual(p.getPositionX(), 0)
        self.assertEqual(p.getPositionY(), 1)
        self.assertEqual(p.getPositionZ(), 2)
        p.setRadius(7)
        self.assertEqual(p.getRadius(), 7)



if __name__ == '__main__':
    unittest.main()
