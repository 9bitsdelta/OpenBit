workspace "OpenBit"
startproject "Sandbox"

configurations { "Debug", "Release" }

architecture "x64"

flags {
    "MultiProcessorCompile"
}

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

vendor = "%{wks.location}/OpenBit/vendor"

-- Include directories relative to root folder (solution directory)
Includes = { }
Includes["spdlog"] = vendor .. "/spdlog/include"
Includes["glm"]    = vendor .. "/glm"
Includes["entt"]    = vendor .. "/entt"

include "OpenBit"
include "Sandbox"
