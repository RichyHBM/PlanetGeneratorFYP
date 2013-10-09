-- A project defines one build target
   project "TestProject"
      location "build"
      kind "ConsoleApp" -- Console Window
      language "C++"
      files {  "./src/**.cpp",
               "./src/**.c",
               "./src/**.hpp", 
               "./src/**.h",
               "./external/src/**.cpp",
               "./external/src/**.c",
               "./external/src/**.hpp", 
               "./external/src/**.h",
               "./test_src/**.cpp",
               "./test_src/**.c",
               "./test_src/**.hpp", 
               "./test_src/**.h", }

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
            links { "sfml-window", "sfml-system", "GLU", "GL" }
         end
		 
         targetdir "./bin/Debug"
 
      configuration "Release"
         --debugdir ("./")
         defines { "NDEBUG", "GLEW_STATIC" }
         flags { "OptimizeSpeed" }
         if _ACTION == "vs2010" then
            links {  "sfml-window", "sfml-system", "glu32", "opengl32" }
         end
         if _ACTION == "gmake" then
            links { "sfml-window", "sfml-system", "GLU", "GL" }
         end
         
         targetdir "./bin/Release"
