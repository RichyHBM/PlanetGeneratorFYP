-- A project defines one build target
project "StandAlone"
	kind "ConsoleApp" -- Console Window
	files {  "../src/standalone/**.cpp",
		"../src/standalone/**.c",
		"../src/standalone/**.hpp",
		"../src/standalone/**.h", }

	includedirs { "../external/include/", "../src/"}
	if _ACTION == "vs2010" then
		links { "Noisepp", "Framework" }
	end

	if _ACTION == "gmake" or _ACTION == "codeblocks" then
		if os.get() == "macosx" then
			links {  "pthread", "Noisepp", "Framework", "AntTweakBar", "sfml-window", "sfml-system", "OpenGL.framework", "CoreFoundation.framework" }
		else
			links {  "pthread", "Noisepp", "Framework", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL" }
		end
	end

	if os.get() == "linux" or os.get() == "macosx" then
		postbuildcommands { "sh ../postbuild/linux.sh" }
	end

	configuration "Debug"
		if _ACTION == "vs2010" then
			links { "AntTweakBar", "sfml-window-d", "sfml-system-d", "glu32", "opengl32" }
		end

	configuration "Release"
		if _ACTION == "vs2010" then
			links { "AntTweakBar", "sfml-window", "sfml-system", "glu32", "opengl32" }
		end
