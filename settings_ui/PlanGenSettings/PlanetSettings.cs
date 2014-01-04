using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PlanGenSettings
{
    public class PlanetSettings
    {
        public double ViewDisplacement = 0.0;
        public int Controls = 0;

        public int Seed = 12345;
        public double Persistance = 0.5;
        public int Octaves = 6;
        public double Frequency = 1.0;
        public int Quality = 1;
        public double Scale = 2.12;
        public double Lacunarity = 2.0;
        public double Distortion = 0.02;

        public int WindowWidth = 800;
        public int WindowHeight = 600;
        public int AntiAliasing = 1;
        public int DepthBits = 24;
        public int StencilBits = 8;
        public int TargetFPS = 60;
        public int VSync = 0;
        public int FullScreen = 0;

        public String[] ToArgumentArray()
        {
            return new List<string>{
                "-viewDisp " + ViewDisplacement,
                "-controls " + Controls,

                "-seed " + Seed,
                "-persistance " + Persistance,
                "-octave " + Octaves,
                "-frequency " + Frequency,
                "-quality " + Quality,
                "-scale " + Scale,
                "-lacunarity " + Lacunarity,
                "-distortion " + Distortion,

                "-depth " + DepthBits,
                "-stencil " + StencilBits,
                "-antialiasing " + AntiAliasing,
                "-width " + WindowWidth,
                "-height " + WindowHeight,
                "-vsynk " + VSync,
                "-fullsceen " + FullScreen ,
                "-fps " + TargetFPS
            }.ToArray();
        }
    }
}
