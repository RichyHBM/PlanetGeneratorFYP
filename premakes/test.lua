-- A project defines one build target
   project "TestProject"
      kind "ConsoleApp" -- Console Window
      files {  "../src/test/**.cpp",
               "../src/test/**.c",
               "../src/test/**.hpp", 
               "../src/test/**.h" }

      includedirs { "../external/include/", "../src/"}
      
      links { "Framework" }