#pragma once
#include "Core/ResourceManager.h"

namespace VOEngine {
	class PlatformUtils {
	public:
		friend ResourceManager;
		//3 functions below do not use filters. Return value is empty string if canceled.
		static std::wstring OpenFileDialog(const std::wstring& filter);
		//static std::wstring SaveFileDialog(const char* filter);
		static std::vector<std::wstring> OpenFilesDialog(const std::wstring& filter);
		static std::wstring OpenFolderDialog(const char* title);
	};
}