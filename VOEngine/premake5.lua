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
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/sndfile/include/ **.h"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/glad/include",
		"vendor/ImGui",
		"vendor/glm/glm",
		"vendor/OpenAL/include",
		"vendor/sndfile/include"
	}

	libdirs {
		"libs/OpenAL"
	}

	links {
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui",
		"OpenAL32.lib"
	}

   filter "configurations:Debug"
      defines { "DEBUG", "LOG", "PROFILING" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

	filter "system:windows"
		systemversion "latest"