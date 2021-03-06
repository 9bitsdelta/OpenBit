project "Kepler"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}/")

    files {
        "source/**"
    }

    includedirs {
        "%{wks.location}/OpenBit/include",
        "%{Includes.spdlog}",
        "%{Includes.glm}",
        "%{Includes.entt}",
        "%{Includes.imgui}",
        "%{Includes.lua}",
        "%{Includes.sol}"
    }

    links {
        "OpenBit"
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "BIT_PLATFORM_WINDOWS"
        }

        links {
            "opengl32.lib"
        }

    filter "system:linux"
        systemversion "latest"
        toolset ("gcc")

        defines {
            "BIT_PLATFORM_LINUX"
        }

        links {
            "X11",
            "pthread",
            "dl",
            "GL",
            "ImGui",
            "GLAD",
            "GLFW"
        }

    filter "configurations:Debug*"
        defines "BIT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release*"
        defines "BIT_RELEASE"
        runtime "Release"
        optimize "on"
        symbols "on"
