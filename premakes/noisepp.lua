-- A project defines one build target
project "Noisepp"
	kind "StaticLib"
	files { "../external/noiseppsrc/utils/*.cpp" }
	includedirs { "../external/include/", 
		"../external/include/noisepp/core/", 
		"../external/include/noisepp/threadpp/", 
		"../external/include/noisepp/utils/" }
	
	configuration "Debug"
		flags { "OptimizeSpeed" }

	configuration "Release"
		flags { "OptimizeSpeed", "NoFramePointer" }
		if _ACTION == "gmake" then
			buildoptions { "-ffast-math -funroll-loops" }
		end
		if _ACTION == "vs2010" or _ACTION == "vs2008" or _ACTION == "vs2005" then
			buildoptions { "/Ox /Ob2 /Oi /Ot /Oy /arch:SSE2 /fp:fast" }
		end
