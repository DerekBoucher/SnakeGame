-- Premake5 BuildScript for snakeGame
-- Author: Derek Boucher
-- In order to build, simply open command line in project folder and execute the following:
-- Xcode (MAC OS):
-- >premake5 xcode4
-- Visual Studio 2013 (Windows):
-- >premake5 vs2013
-- Visual Studio 2015 (Windows):
-- >premake5 vs2015
-- Visual Studio 2017 (Windows):
-- >premake5 vs2017

-- Then simply open project in IDE and build.

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