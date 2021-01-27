workspace "OpenBit"
startproject "Sandbox"

configurations { "Debug", "Release" }

architecture "x64"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

vendor = "%{wks.location}/OpenBit/vendor"

-- Include directories relative to root folder (solution directory)
Includes = { }
Includes["spdlog"] = vendor .. "/spdlog/include"
Includes["glm"]    = vendor .. "/glm"

include "OpenBit"
include "Sandbox"
