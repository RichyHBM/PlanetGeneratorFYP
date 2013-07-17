-- A solution contains projects, and defines the available configurations
solution "Framework"
   configurations { "Debug", "Release" }
   location "build"

-- A project defines one build target
   project "Framework"
      location "build"
      kind "ConsoleApp" -- Console Window
      language "C++"
      files { "./src/**.cpp","./src/**.c","./src/**.hpp", "./src/**.h","../externSRC/**.cpp","../externSRC/**.c","../externSRC/**.hpp", "../externSRC/**.h"  }
      excludes { "../externSRC/SOIL/original/*" }
      includedirs { "../include/"}
 
      configuration "Debug"
         --debugdir ("./")
         defines { "DEBUG", "GLEW_STATIC"}
         flags { "Symbols" }
         links {"glfw", "GLU", "GL"} --"glfw", "glu32", "opengl32" for windows
         targetname ("Frameworkd")
         targetdir "./bin/Debug"
 
      configuration "Release"
	 --debugdir ("./")
         defines { "NDEBUG", "GLEW_STATIC" }
         flags { "OptimizeSpeed" }
         links {  "glfw", "GLU", "GL" }
         targetdir "./bin/Release"
