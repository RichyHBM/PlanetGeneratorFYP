-- A project defines one build target
   project "StandAlone"
      kind "ConsoleApp" -- Console Window
      files {  "../src/standalone/**.cpp",
               "../src/standalone/**.c",
               "../src/standalone/**.hpp", 
               "../src/standalone/**.h", }

      includedirs { "../external/include/", "../src/"}
      
      links { "Framework" }