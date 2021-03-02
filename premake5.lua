outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

workspace "Nyx"
	architecture "x64"
	startproject "Example"
	language "C++"
	cppdialect "C++17"

	configurations {
		"Debug",
		"Testing",
		"Release",
	}

	flags {
		"FatalCompileWarnings", "MultiProcessorCompile"
	}

	disablewarnings "4201"
	warnings "Extra"


project "Nyx"
	location "Nyx"
	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir	("bin-obj/"..outputdir.."/%{prj.name}")

	pchheader "nyx_pch.hpp"
	pchsource "%{prj.name}/src/nyx_pch.cpp"

	files "%{prj.name}/src/**"

	includedirs {
		"%{prj.location}/src",
		"%{wks.location}/deps/*/include"
	}

	libdirs "%{wks.location}/deps/*/lib/%{cfg.system}-%{cfg.architecture}"

	links {
		"glfw3.lib",
		"glew32s.lib",
		"opengl32.lib"
	}

	defines "GLEW_STATIC"

	filter "system:windows"
		defines { "NYX_PLATFORM_WINDOWS" }
		systemversion "latest"

	filter "configurations:Debug"
		defines { "NYX_DEBUG" }
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Testing"
		defines { "NYX_ENABLE_LOGGER" }
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


project "Example"
	location "Example"
	kind "ConsoleApp"
	staticruntime "on"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-obj/" ..outputdir.. "/%{prj.name}")

	files "%{prj.name}/src/**"

	includedirs {
		"%{prj.location}/src",
		"%{wks.location}/deps/*/include",
		"%{wks.location}/Nyx/src"
	}

	links {
		"Nyx"
	}

	defines "GLEW_STATIC"

	filter "system:windows"
		defines { "NYX_PLATFORM_WINDOWS" }
		systemversion "latest"

	filter "configurations:Debug"
		defines { "NYX_DEBUG" }
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Testing"
		defines { "NYX_ENABLE_LOGGER" }
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"