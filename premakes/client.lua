-- A project defines one build target
   project "Client"
      kind "ConsoleApp" -- Console Window
      files {  "../src/client/**.cpp",
               "../src/client/**.c",
               "../src/client/**.hpp", 
               "../src/client/**.h" }      

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
