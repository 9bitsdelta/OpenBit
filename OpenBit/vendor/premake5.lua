project "GLAD"
    location "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}/")

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

project "GLFW"
    location "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.name}/include"
    }

    files {
        "%{prj.name}/src/glfw_config.h",
        "%{prj.name}/src/context.c",
        "%{prj.name}/src/init.c",
        "%{prj.name}/src/input.c",
        "%{prj.name}/src/monitor.c",
        "%{prj.name}/src/vulkan.c",
        "%{prj.name}/src/window.c",
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files {
            "%{prj.name}/src/win32_init.c",
            "%{prj.name}/src/win32_joystick.c",
            "%{prj.name}/src/win32_monitor.c",
            "%{prj.name}/src/win32_thread.c",
            "%{prj.name}/src/win32_time.c",
            "%{prj.name}/src/win32_window.c",
            "%{prj.name}/src/wgl_context.c",
            "%{prj.name}/src/egl_context.c",
            "%{prj.name}/src/osmesa_context.c"
        }
        
    filter "system:linux"
    	systemversion "latest"
    	toolset ("gcc")
    	
        defines {
            "_GLFW_X11",
            "_CRT_SECURE_NO_WARNINGS"
        }

    	files {
            "%{prj.name}/src/x11_init.c",
            "%{prj.name}/src/x11_monitor.c",
            "%{prj.name}/src/x11_window.c",
            "%{prj.name}/src/xkb_unicode.c",
            "%{prj.name}/src/posix_time.c",
            "%{prj.name}/src/posix_thread.c",
            "%{prj.name}/src/glx_context.c",
            "%{prj.name}/src/egl_context.c",
            "%{prj.name}/src/osmesa_context.c",
            "%{prj.name}/src/linux_joystick.c",
    	}    
        

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "ImGui"
    location "ImGui"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/imconfig.h",
		"%{prj.name}/imgui.h",
		"%{prj.name}/imgui.cpp",
		"%{prj.name}/imgui_draw.cpp",
		"%{prj.name}/imgui_internal.h",
		"%{prj.name}/imgui_widgets.cpp",
		"%{prj.name}/imstb_rectpack.h",
		"%{prj.name}/imstb_textedit.h",
		"%{prj.name}/imstb_truetype.h",
        "%{prj.name}/imgui_tables.cpp",
		"%{prj.name}/imgui_demo.cpp"
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

project "lua"
	location "lua"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**"
    }

    removefiles {
        "%{prj.name}/src/lua.c",
        "%{prj.name}/src/lua.h",
        "%{prj.name}/src/luac.c"
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