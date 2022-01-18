include "./vendor/premake/premake-customization/solution_items.lua"

workspace ("VOEngine")
	configurations {"Debug","Release"}
	architecture "x64"
	startproject "Sandbox"

outputDir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group ""

include "VOEngine"
include "Sandbox"
include "VOEngine/vendor/GLFW"