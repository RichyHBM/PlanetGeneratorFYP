-- A project defines one build target
project "Sandbox"
	kind "ConsoleApp" -- Console Window
	files {  "../src/sandbox/**.cpp",
		"../src/sandbox/**.c",
		"../src/sandbox/**.hpp", 
		"../src/sandbox/**.h" }

	includedirs { "../external/include/", "../src/"}
	if _ACTION == "vs2010" then
			links {  "Framework" }
		end 