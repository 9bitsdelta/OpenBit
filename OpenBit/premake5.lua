project "OpenBit"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}" )
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "bitpch.h"
    pchsource "source/bitpch.cpp"

    files {
        "source/**",
        "include/**"
    }

    includedirs {
        "include",
        "%{Includes.spdlog}",
        "%{Includes.glm}",
        "%{Includes.entt}",
        "%{Includes.glad}",
        "%{Includes.glfw}",
        "%{Includes.imgui}",
        "%{Includes.lua}",
        "%{Includes.sol}",
        "%{Includes.stbi}"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    links {
        "ImGui",
        "GLAD",
        "GLFW",
        "lua"
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
        toolset("gcc")

        defines {
            "BIT_PLATFORM_LINUX"
        }

        links {
            "X11",
            "pthread",
            "dl",
            "GL",
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
