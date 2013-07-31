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
      if _ACTION == "vs2010" then
         libdirs { "./external/lib/vs" }
         defines { "WIN32"}
		 --postbuildcommands { "xcopy ./Resources ./build/Resources /e /i /h" }
      end
      if _ACTION == "codeblocks" or _ACTION == "mingw" then
         libdirs { "./external/lib/mingw" }
         linkoptions { "-mwindows" }
		 --postbuildcommands { "xcopy \"../Resources\" \"../build/Resources\" /e /i /h" }
      end
      
      configuration "Debug"
         --debugdir ("./")
         defines { "DEBUG", "GLEW_STATIC"}
         flags { "Symbols" }
         if _ACTION == "vs2010" then
            links { "glfw3d", "glu32", "opengl32", "freetype250_D" }
         end 
         if _ACTION == "codeblocks" or _ACTION == "mingw" then
            links { "libglfw3d", "libglu32", "libopengl32", "libfreetype" }
         end
         targetname ("PlanetGeneratorFYPd")
         targetdir "./bin/Debug"
 
      configuration "Release"
         --debugdir ("./")
         defines { "NDEBUG", "GLEW_STATIC" }
         flags { "OptimizeSpeed" }
         if _ACTION == "vs2010" then
            links { "glfw3", "glu32", "opengl32", "freetype250" }
         end
         if _ACTION == "codeblocks" or _ACTION == "mingw" then
            links { "libglfw3", "libglu32", "libopengl32", "libfreetype" }
         end
         targetdir "./bin/Release"
