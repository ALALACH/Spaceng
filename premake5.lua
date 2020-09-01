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

group "Buildblocks"
project "Spaceng"
	location "Spaceng"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"%{prj.name}/src"
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
		"SE_PLATFORM_WIN"
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




group "Applications"
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
		"Spaceng/src"
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
			"SE_PLATFORM_WIN"
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