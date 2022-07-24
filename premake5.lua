--[[
The indentation in this file has nothing to do with lua and more with how premake5 organizes everything.
All settings created in the workspace will be applied to all projects in the workspace.

In this case all the settings here will be default for all our dependencies as well.
]]--
workspace "tutorial"
	-- We are only building for 64bit platforms.
	architecture "x86_64"
	startproject "tutorial"
	-- These are the configurations; these nothing on their own.
	configurations { "debug", "release" }
	language "C++"
	cppdialect "C++20"
	cdialect "C11"
	-- Link the runtime statically. This slightly increases the size of the binary.
	-- However, will not have to load the standard library at runtime.
	staticruntime "On"
	-- For all configurations we will generate debug symbols.
	-- These aren't typically distributed with the release binaries.
	symbols "On"
	-- Set projects to be static libs by default.
	kind "StaticLib"
	--[[
	These specify the output files for the generated code.
	Premake provides some tokens to use for this.
	Since we only build for x86_64, architecture is left out.
	Premake5 will automcatically create these directories if they don't exist.
	]]--
	targetdir "bin/%{cfg.system}-%{cfg.buildcfg}/%{prj.name}"
	objdir "bin-int/%{cfg.system}-%{cfg.buildcfg}/%{prj.name}"
	--[[
	These specify the configuration settings.
	For debug use minimal optimizations that allow stepping through the code.
	For release optimize for speed.
	Both configurations specify their respective runtime libraries.
	]]-- 
	filter "configurations:debug"
		optimize "Debug"
		runtime "Debug"
	filter "configurations:release"
		optimize "Speed"
		runtime "Release"
	-- systemversion only applies to windows
	filter "system:windows"
		systemversion "latest"
-- Create the main project. Must match `startproject` in the workspace.
project "tutorial"
	-- Specify where the location of the project file should go.
	location "tutorial"
	-- Specify the project to create a console application.
	kind "ConsoleApp"
	-- Specify the files to include in the project.
	files
	{
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.h"
	}
	-- Specify the include directories.
	includedirs "%{prj.location}/src"