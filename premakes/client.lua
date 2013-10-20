-- A project defines one build target
   project "Client"
      kind "ConsoleApp" -- Console Window
      files {  "../src/client/**.cpp",
               "../src/client/**.c",
               "../src/client/**.hpp", 
               "../src/client/**.h" }      

      includedirs { "../external/include/", "../src/"}    
