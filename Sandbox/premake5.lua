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
		"%{wks.location}/VOEngine/vendor/spdlog/include",
		"%{wks.location}/VOEngine/vendor/GLFW/include",
		"%{wks.location}/VOEngine/vendor/Glad/include",
		"%{wks.location}/VOEngine/vendor/ImGui",
		"%{wks.location}/VOEngine/vendor/glm/glm",
		"%{wks.location}/VOEngine/vendor/yaml-cpp/include",
		"%{wks.location}/VOEngine/vendor/OpenAL/include",
		"%{wks.location}/VOEngine/vendor/sndfile/include"
	}

   filter "configurations:Debug"
      defines { "DEBUG", "LOG", "PROFILING" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

	filter "system:windows"
		systemversion "latest"
		postbuildcommands { 
			'copy "%{wks.location}\\%{prj.name}\\settings.yaml" "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\settings.yaml"',
			'mkdir "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\res"',
			'mkdir "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\res\\sounds"',
			'mkdir "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\res\\shaders"',
			'copy "%{wks.location}\\%{prj.name}\\res\\sounds\\**.**" "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\res\\sounds\\**.**"',
			'copy "%{wks.location}\\%{prj.name}\\res\\Shaders\\**.**" "%{wks.location}\\bin\\' .. outputDir .. '\\%{prj.name}\\res\\shaders\\**.**"'
		}