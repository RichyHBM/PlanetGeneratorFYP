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
      if _ACTION == "gmake" or _ACTION == "codeblocks" then
         postbuildcommands { "sh ../postbuild/linux.sh" }
      end

      configuration "Debug"
         if _ACTION == "gmake" or _ACTION == "codeblocks" then
            links { "pthread", "AntTweakBar", "sfml-network", "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
         end

      configuration "Release"
         if _ACTION == "gmake" or _ACTION == "codeblocks" then
            links { "pthread", "AntTweakBar", "sfml-network", "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
         end
		
	configuration "Linux64"
		links { "pthread", "sfml-network64", "sfml-window64", "sfml-system64", "GLU", "GL", "noisepp64" }
	