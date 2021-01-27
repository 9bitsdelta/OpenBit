-- no longer included, kept for legacy reasons... kinda

project "glad"
    location "glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir)
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/include/glad/glad.h",
        "%{prj.name}/include/KHR/khrplatform.h",
        "%{prj.name}/src/glad.c"
    }

    includedirs {
        "%{prj.name}/include"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"
        toolset("gcc")

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "glfw"
    location "glfw"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir)
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.name}/include"
    }

    filter "system:windows"
        systemversion "latest"

        files {
            "%{prj.name}/src/win32_init.c",
            "%{prj.name}/src/win32_joystick.c",
            "%{prj.name}/src/win32_monitor.c",
            "%{prj.name}/src/win32_thread.c",
            "%{prj.name}/src/win32_time.c",
            "%{prj.name}/src/win32_window.c",

        }
