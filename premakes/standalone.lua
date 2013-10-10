-- A project defines one build target
   project "StandAlone"
      kind "ConsoleApp" -- Console Window
      files {  "../src/standalone/**.cpp",
               "../src/standalone/**.c",
               "../src/standalone/**.hpp", 
               "../src/standalone/**.h", }

      includedirs { "../external/include/", "../src/"}
      
      configuration "Debug"
         if _ACTION == "vs2010" then
            links { "Framework", "sfml-window-d", "sfml-system-d", "glu32", "opengl32" }
         end 
         if _ACTION == "gmake" then
            links { "Framework", "sfml-window", "sfml-system", "GLU", "GL" }
         end
 
      configuration "Release"
         if _ACTION == "vs2010" then
            links {  "Framework", "sfml-window", "sfml-system", "glu32", "opengl32" }
         end
         if _ACTION == "gmake" then
            links { "Framework", "sfml-window", "sfml-system", "GLU", "GL" }
         end
