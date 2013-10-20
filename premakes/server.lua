-- A project defines one build target
   project "Server"
      kind "ConsoleApp" -- Console Window
      files {  "../src/server/**.cpp",
               "../src/server/**.c",
               "../src/server/**.hpp", 
               "../src/server/**.h" }

      includedirs { "../external/include/", "../src/"}
      
      links { "Framework" }