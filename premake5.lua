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
-- Visual Studio 2019 (Windows):
-- >premake5 vs2019

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

		files { "src/**.h", "src/**.cpp" }

			filter { 'configurations:Debug', "system:macosx" }
				postbuildcommands
				{
					"{COPY} Assets/ bin/%{cfg.buildcfg}/Assets"
				}
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
			filter{ 'configurations:Release', "system:macosx" }
				postbuildcommands
				{
					"{COPY} Assets/ bin/%{cfg.buildcfg}/Assets"
				}
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
			filter{ 'configurations:Dist', "system:macosx" }
				postbuildcommands
				{
					"{COPY} Assets/ bin/%{cfg.buildcfg}/Assets"
				}
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

		filter "system:windows"
			defines { "SDL_MAIN_HANDLED" }
			postbuildcommands
			{
				"copy lib\\Windows\\SDL2-2.0.8\\lib\\x86\\SDL2.dll bin\\%{cfg.buildcfg}\\SDL2.dll",
				"copy lib\\Windows\\SDL2_image-2.0.3\\lib\\x86\\SDL2_image.dll bin\\%{cfg.buildcfg}\\SDL2_image.dll",
				"copy lib\\Windows\\SDL2_image-2.0.3\\lib\\x86\\libpng16-16.dll bin\\%{cfg.buildcfg}\\libpng16-16.dll",
				"copy lib\\Windows\\SDL2_image-2.0.3\\lib\\x86\\zlib1.dll bin\\%{cfg.buildcfg}\\zlib1.dll",
				"XCOPY Assets /E /Y bin\\%{cfg.buildcfg}\\Assets\\"
			}
			systemversion "latest"
			links
			{
				"SDL2",
				"SDL2main",
				"SDL2_image"
			}
			libdirs
			{
				"%{prj.location}/lib/Windows/SDL2-2.0.8/lib/x86",
				"%{prj.location}/lib/Windows/SDL2_image-2.0.3/lib/x86"
			}
			includedirs
			{
				"%{prj.location}/src/main/headers",
				"%{prj.location}/lib/Windows/SDL2-2.0.8/include",
				"%{prj.location}/lib/Windows/SDL2_image-2.0.3/include"
			}
