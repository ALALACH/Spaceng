workspace "Spaceng"
	architecture "x64"
	targetdir "build"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--includeDir init
IncludeDir = {}
IncludeDir["glfw"] = "Spaceng/Dependency/glfw/include"
IncludeDir["imgui"] = "Spaceng/Dependency/imgui"
IncludeDir["spdlog"] = "Spaceng/Dependency/spdlog"




include "Spaceng/Dependency/glfw"
include "Spaceng/Dependency/imgui"
--include "Spaceng/Dependency/spdlog"

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
		"%{prj.name}/Dependency",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}"
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
		"glfw",
		"imgui"
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
		"Spaceng/Dependency"
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