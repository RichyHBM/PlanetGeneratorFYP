-- A solution contains projects, and defines the available configurations
solution "PlanetGeneratorFYP"
   configurations { "Debug", "Release" }
   location "./build"
   defines { "SFML", "GLEW_STATIC" }
   language "C++"

   if _ACTION == "vs2010" then
      libdirs { "./external/lib/vs2010" }
      defines { "WIN32" }
      postbuildcommands { "call ..\\postbuild\\vs.bat" }
   end

   if _ACTION == "gmake" then
      libdirs { "./external/lib/linux" }
   end

   configuration "Debug"
      targetdir "./bin/Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   configuration "Release"
      targetdir "./bin/Release"
      defines { "NDEBUG" }
      flags { "OptimizeSpeed" }

   dofile "./premakes/standalone.lua"
   dofile "./premakes/framework.lua"
   dofile "./premakes/test.lua"
   dofile "./premakes/server.lua"
   dofile "./premakes/client.lua"
