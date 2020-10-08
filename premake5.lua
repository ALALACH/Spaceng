workspace "Spaceng"
	architecture "x64"
	targetdir "build"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Editor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--includeDir init
IncludeDir = {}
IncludeDir["glfw"] = "Spaceng/Dependencies/glfw/include"

group"Dependencies"
include "Spaceng/Dependencies/glfw"

group "Buildblock-Tier1"
project "Spaceng"
	location "Spaceng"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "Spaceng/src/PCH.cpp"

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Dependencies",
		"%{IncludeDir.glfw}"
	}

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}

	links 
	{ 
		"glfw"
	}

	filter "system:windows"
	systemversion "latest"
	
	defines 
	{ 
		"SE_PLATFORM_WIN",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		symbols "On"
				
	filter "configurations:Release"
		defines "SE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SE_DIST"
		optimize "On"





group "Client"
project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
		"Spaceng"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"Spaceng/src",
		"Spaceng/Dependencies"
	}
	
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	filter "system:windows"
		systemversion "latest"
				
		defines 
		{ 
			"SE_PLATFORM_WIN",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "configurations:Debug"
		defines "SE_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "SE_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "SE_DIST"
		optimize "on"