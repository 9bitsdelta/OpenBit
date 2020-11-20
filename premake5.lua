workspace "OpenBit"
startproject "Sandbox"

configurations { "Debug", "Release" }

architecture "x64"

outputdir = "%{cfg.buildcfg}"

vendordir = "OpenBit/vendor"

-- Include directories relative to root folder (solution directory)
IncludeDir = { }

group "Dependencies"
	include (vendordir)

group ""

include "OpenBit"
include "Sandbox"