project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")
	links {"VOEngine"}
	staticruntime "off"

	files {
		"src/**.h",
		"src/**.cpp"	
	}

	includedirs {
		"%{wks.location}/VOEngine/src",
		"%{wks.location}/VOEngine/pch"
	}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

	filter "system:windows"
		systemversion "latest"