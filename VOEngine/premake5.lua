project "VOEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "vopch.h"
	pchsource "src/vopch.cpp"
	staticruntime "off"

	files {
		"**.h",
		"**.cpp"	
	}

	includedirs {
		"src",
		"vendor/spdlog/include"
	}

   filter "configurations:Debug"
      defines { "DEBUG", "LOG", "PROFILING" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

	filter "system:windows"
		systemversion "latest"