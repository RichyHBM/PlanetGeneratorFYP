using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PlanGenSettings
{
    public class PlanetSettings
    {
        public int Controls = 0;

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
                "-controls " + Controls,

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
