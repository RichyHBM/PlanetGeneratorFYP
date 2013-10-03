-- A solution contains projects, and defines the available configurations
solution "PlanetGeneratorFYP"
   configurations { "Debug", "Release" }
   location "build"

-- A project defines one build target
   project "PlanetGeneratorFYP"
      location "build"
      kind "ConsoleApp" -- Console Window
      language "C++"
      files { "./src/**.cpp","./src/**.c","./src/**.hpp", "./src/**.h","./external/src/**.cpp","./external/src/**.c","./external/src/**.hpp", "./external/src/**.h" }
      includedirs { "./external/include/"}
      defines{ "SFML" }
      if _ACTION == "vs2010" then
         libdirs { "./external/lib/vs2010" }
         defines { "WIN32" }
		   postbuildcommands { "call ..\\postbuild\\vs.bat" }
      end

      if _ACTION == "gmake" then
         libdirs { "./external/lib/linux" }
      end
      
      configuration "Debug"
         --debugdir ("./")
         defines { "DEBUG", "GLEW_STATIC"}
         flags { "Symbols" }
         if _ACTION == "vs2010" then
            links { "sfml-window-d", "sfml-system-d", "glu32", "opengl32" }
         end 
         if _ACTION == "gmake" then
            links { "libsfml-window-d", "libsfml-system-d", "libGLU", "libGL" }
         end
		 
         targetname ("PlanetGeneratorFYPd")
         targetdir "./bin/Debug"
 
      configuration "Release"
         --debugdir ("./")
         defines { "NDEBUG", "GLEW_STATIC" }
         flags { "OptimizeSpeed" }
         if _ACTION == "vs2010" then
            links {  "sfml-window", "sfml-system", "glu32", "opengl32" }
         end
         if _ACTION == "gmake" then
            links { "libsfml-window", "libsfml-system", "libGLU", "libGL" }
         end
         
         targetdir "./bin/Release"
