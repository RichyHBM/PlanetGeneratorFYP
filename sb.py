#!/usr/bin/env python

import os

Frequency = 1
Octaves = 6
Seed = 1234
Quality = 1
Lacunarity = 2
Persistence = 0.5
Scale = 2.12
distortion = 0.001
fileName = "%d_%d_%f_%d_%d_%f_%d_%f.bmp" % (Seed, Octaves, Persistence, Frequency, Quality, Scale, Lacunarity, distortion)

cmd = "./Sandbox %d %d %f %d %d %f %d %f %s" % (Seed, Octaves, Persistence, Frequency, Quality, Scale, Lacunarity, distortion, fileName)
print cmd
os.system (cmd)
