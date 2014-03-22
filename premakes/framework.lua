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
	  
      configuration "Debug"
         if _ACTION == "gmake" or _ACTION == "codeblocks" then
            links { "pthread", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
         end

      configuration "Release"
         if _ACTION == "gmake" or _ACTION == "codeblocks" then
            links { "pthread", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
         end