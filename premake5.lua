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
project "tutorial"
	location "tutorial"
	kind "ConsoleApp"
	files
	{
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.h"
	}
	-- We must specify the glfw include directyory in addition to our existing one
	includedirs
	{
		"%{prj.location}/src",
		"%{wks.location}/vendor/glfw/include"
	}
	--[[
	This section defines what to be linked with at compile time.
	Premake makes it very easy to link other project just my specifying the project name
	]]--
	links "glfw"
	--[[
	On linux we must link with additional dependencies to allow glfw to function.
	If these are not defined as a project, it will add the -l flag to the linker command.
	]]--
	filter "system:linux"
		links
		{
			"dl",
			"pthread",
			"X11"
		}
	-- On macosx we must link against these
	filter "system:macosx"
		links
		{
			"CoreFoundation.framework",
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework"
		}
project "glfw"
	location "vendor/glfw"
	-- We set the default language to C++, GLFW is a C api so we override it here
	language "C"
	-- These files must be compiled on all platforms
	files
	{
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/egl_context.c",
		"%{prj.location}/src/egl_context.h",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/internal.h",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/osmesa_context.c",
		"%{prj.location}/src/osmesa_context.h",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c"
	}
	-- These files must be compiled on windows
	filter "system:windows"
		files
		{
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/wgl_context.h",
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_joystick.h",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_platform.h",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_window.c"
		}
		-- GLFW requires us to select the windowing API at compile time, for windows we use WIN32, 
		-- additionally glfw doesn't use the windows CRT functions so we silence the warnings
		defines { "_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS" }
	-- These files must be compiled on linux
	filter "system:linux"
		files
		{
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/glx_context.h",
			"%{prj.location}/src/linux_joystick.c",
			"%{prj.location}/src/linux_joystick.h",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_time.h",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_thread.h",
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_platform.h",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/xkb_unicode.h"
		}
		-- For linux we are using the X11 api
		defines "_GLFW_X11"
	-- These files must be compiled on macosx
	filter "system:macosx"
		files
		{
			"%{prj.location}/src/cocoa_init.m",
			"%{prj.location}/src/cocoa_joystick.m",
			"%{prj.location}/src/cocoa_joystick.h",
			"%{prj.location}/src/cocoa_monitor.m",
			"%{prj.location}/src/cocoa_platform.h",
			"%{prj.location}/src/cocoa_time.c",
			"%{prj.location}/src/cocoa_window.m",
			"%{prj.location}/src/nsgl_context.m",
			"%{prj.location}/src/nsgl_context.h",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_thread.h"
		}
		-- For macosx we are using the Cocoa api
		defines "_GLFW_COCOA"