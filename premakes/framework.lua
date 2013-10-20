-- A project defines one build target
   project "Framework"
      kind "StaticLib"
      files {  "../src/framework/**.cpp",
               "../src/framework/**.c",
               "../src/framework/**.hpp", 
               "../src/framework/**.h",
               "../external/src/**.cpp",
               "../external/src/**.c",
               "../external/src/**.hpp",
               "../external/src/**.h" }

      includedirs { "../external/include/"} 

	   if _ACTION == "vs2010" then
         postbuildcommands { "call ..\\postbuild\\vs.bat" }
      end    

   configuration "Debug"
      if _ACTION == "vs2010" then
         links { "sfml-window-d", "sfml-system-d", "glu32", "opengl32", "noisepp-d" }
      end 
      if _ACTION == "gmake" then
         links { "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
      end


   configuration "Release"
      if _ACTION == "vs2010" then
         links { "sfml-window", "sfml-system", "glu32", "opengl32", "noisepp" }
      end
      if _ACTION == "gmake" then
         links { "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
      end
