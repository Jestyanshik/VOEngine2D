#include <vopch.h>

namespace VOEngine {
	class PlatformUtils {
	public:
		//3 functions below do not use filters. Return value is empty string if canceled.
		static std::wstring OpenFileDialog(const char* filter);
		//static std::wstring SaveFileDialog(const char* filter);
		static std::vector<std::wstring> OpenFilesDialog(const char* filter);
		static std::wstring OpenFolderDialog(const char* title);
		//Should return value more than 32 into outDone variable
		static void executeCommand(const std::string& file,const std::string& command);
		static void executeMultipleCommands(const std::string& file, const std::vector<std::string>& commands, unsigned long& outDone);

	};


}