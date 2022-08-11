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
		"%{wks.location}/VOEngine/pch",
		"%{wks.location}/VOEngine/vendor/spdlog/include",
		"%{wks.location}/VOEngine/vendor/GLFW/include",
		"%{wks.location}/VOEngine/vendor/Glad/include",
		"%{wks.location}/VOEngine/vendor/ImGui",
		"%{wks.location}/VOEngine/vendor/glm/glm"

	}

   filter "configurations:Debug"
      defines { "DEBUG", "LOG", "PROFILING" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

	filter "system:windows"
		systemversion "latest"