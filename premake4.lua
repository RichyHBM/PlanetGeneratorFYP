-- A solution contains projects, and defines the available configurations
solution "PlanetGeneratorFYP"
	configurations { "Debug", "Release" }
	location "./build"
	defines { "SFML", "GLEW_STATIC" }
	language "C++"

	if _ACTION == "vs2010" then
		libdirs { "./external/lib/vs2010" }
		defines { "WIN32", "_CRT_SECURE_NO_WARNINGS" }
		buildoptions { "/wd4290" }
	end

	if _ACTION == "gmake" then
		libdirs { "./external/lib/linux" }
	end

	configuration "Debug"
		targetdir "./bin/Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

		if _ACTION == "vs2010" then
			links { "sfml-network-d", "sfml-window-d", "sfml-system-d", "glu32", "opengl32", "noisepp-d" }
		end 
		if _ACTION == "gmake" or _ACTION == "codeblocks" then
			links {  "Framework", "pthread", "sfml-network", "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
		end

	configuration "Release"
		targetdir "./bin/Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }

		if _ACTION == "vs2010" then
			links { "sfml-network", "sfml-window", "sfml-system", "glu32", "opengl32", "noisepp" }
		end
		if _ACTION == "gmake" or _ACTION == "codeblocks" then
			links {  "Framework", "pthread", "sfml-network", "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
		end
		
	configuration "Linux64"
		targetdir "./bin/Release64"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }
		links {  "Framework", "pthread", "sfml-network64", "sfml-window64", "sfml-system64", "GLU", "GL", "noisepp64" }
	
	dofile "./premakes/standalone.lua"
	dofile "./premakes/test.lua"
	dofile "./premakes/sandbox.lua"
	dofile "./premakes/framework.lua"
