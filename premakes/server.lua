-- A project defines one build target
   project "Server"
      kind "ConsoleApp" -- Console Window
      files {  "../src/server/**.cpp",
               "../src/server/**.c",
               "../src/server/**.hpp", 
               "../src/server/**.h" }

      includedirs { "../external/include/", "../src/"}
      
    configuration "Debug"
      if _ACTION == "vs2010" then
         links { "Framework", "sfml-window-d", "sfml-system-d", "glu32", "opengl32", "noisepp-d" }
      end 
      if _ACTION == "gmake" then
         links { "Framework", "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
      end


    configuration "Release"
      if _ACTION == "vs2010" then
         links { "Framework", "sfml-window", "sfml-system", "glu32", "opengl32", "noisepp" }
      end
      if _ACTION == "gmake" then
         links { "Framework", "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
      end