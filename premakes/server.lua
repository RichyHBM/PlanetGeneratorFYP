-- A project defines one build target
project "Server"
	kind "ConsoleApp" -- Console Window
	files {  "../src/server/**.cpp",
		"../src/server/**.c",
		"../src/server/**.hpp", 
		"../src/server/**.h" }

	includedirs { "../external/include/", "../src/"}
	
	configuration "Debug64"
		targetdir "../bin/Debug64"
		defines { "DEBUG" }
		flags { "Symbols" }
        links {  "Framework", "pthread", "AntTweakBar64", "sfml-window64", "sfml-system64", "GLU", "GL", "noisepp64" }
	
		
	configuration "Release64"
		targetdir "../bin/Release64"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }
        links {  "Framework", "pthread", "AntTweakBar64", "sfml-window64", "sfml-system64", "GLU", "GL", "noisepp64" }
	
