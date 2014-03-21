-- A solution contains projects, and defines the available configurations
solution "PlanetGeneratorFYP"
	configurations { "Debug", "Release" }
    if _ACTION ~= nil then
        location ( "./build/" .. _ACTION)
    end
	defines { "SFML", "GLEW_STATIC" }
	language "C++"

	if _ACTION == "vs2010" then
		libdirs { "./external/lib/vs2010" }
		defines { "WIN32", "_CRT_SECURE_NO_WARNINGS" }
		buildoptions { "/wd4290" }
		postbuildcommands { "call ..\\postbuild\\vs.bat" }
	end

	if _ACTION == "gmake" then
		libdirs { "./external/lib/linux" }
		postbuildcommands { "sh ../postbuild/linux.sh", "sh ../postbuild/linux64.sh" }
	end

	configuration "Debug"
		targetdir "./bin/Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

		if _ACTION == "vs2010" then
			links { "AntTweakBar", "sfml-window-d", "sfml-system-d", "glu32", "opengl32", "noisepp-d" }
		end 
		if _ACTION == "gmake" or _ACTION == "codeblocks" then
			links {  "Framework", "pthread", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL", "noisepp-d" }
		end

	configuration "Release"
		targetdir "./bin/Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }

		if _ACTION == "vs2010" then
			links { "AntTweakBar", "sfml-window", "sfml-system", "glu32", "opengl32", "noisepp" }
		end
		if _ACTION == "gmake" or _ACTION == "codeblocks" then
			links {  "Framework", "pthread", "AntTweakBar", "sfml-window", "sfml-system", "GLU", "GL", "noisepp" }
		end
		
	dofile "./premakes/standalone.lua"
	dofile "./premakes/server.lua"
	dofile "./premakes/framework.lua"
