-- Premake5 BuildScript for snakeGame

workspace "snakeGame"
	configurations { "Debug", "Release", "Dist" }
	architecture "x86"

	project "snakeGame"
		kind "ConsoleApp"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		objdir 	"obj/"
		cppdialect "C++17"

		files { "**.h", "**.cpp" }

		filter "system:macosx"
			links
			{
				"SDL2.framework",
				"SDL2_image.framework"
			}
			buildoptions 
			{
				"-F %{prj.location}/lib/MacOS"
			}
			linkoptions 
			{
				"-F %{prj.location}/lib/MacOS"
			}