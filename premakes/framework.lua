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