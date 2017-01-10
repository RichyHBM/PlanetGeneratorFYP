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

	if os.get() == "macosx" then
		links {  "pthread", "Noisepp", "AntTweakBar", "sfml-window", "sfml-system", "OpenGL.framework", "CoreFoundation.framework" }
	else
		links { "pthread", "Noisepp", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL" }
	end
