project "OpenBit"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir)

	pchheader "bitpch.h"
	pchsource "source/bitpch.cpp"

	files
	{
		"source/**",
		"include/**"
	}
	
	includedirs
	{
		"include",
		"vendor/spdlog/include"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"BIT_PLATFORM_WINDOWS"
		}
		
		links
		{
			"opengl32.lib"
		}
		
	filter "system:linux"
		systemversion "latest"
		toolset("gcc")

		defines
		{
			"BIT_PLATFORM_LINUX"
		}
		
		links
		{
			"GL",
			"X11",
			"pthread",
			"dl"
		}
		
	filter "configurations:Debug*"
		defines "BIT_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release*"
		defines "BIT_RELEASE"
		runtime "Release"
		optimize "on"