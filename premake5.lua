workspace "OpenBit"
startproject "Sandbox"

configurations { "Debug", "Release" }

architecture "x64"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

vendordir = "OpenBit/vendor"

-- Include directories relative to root folder (solution directory)
IncludeDir = { }

include "OpenBit"
include "Sandbox"
