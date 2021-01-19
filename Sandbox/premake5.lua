project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}/")
	
	files
	{
		"source/**"
	}
	
	includedirs
	{
		"%{wks.location}/OpenBit/include",
		"%{wks.location}/OpenBit/vendor/spdlog/include"
	}
	
	links
	{
		"OpenBit"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BIT_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		systemversion "latest"
		toolset ("gcc")
	
		defines
		{
			"BIT_PLATFORM_LINUX"
		}
	
		links
		{
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
	
