#include "vopch.h"
#ifdef _WIN32
#include "../PlatformUtils.h"
#include "../Utils.h"
#include "core/ResourceManager.h"
#include "core/Rendering/Windows/GLFWWindow/GLFWWindow.h"

#include <commdlg.h>
#include <shobjidl_core.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace VOEngine {
	//TODO: Add support for filters
	std::wstring PlatformUtils::OpenFileDialog(const char* filter) {
		std::wstring outFolderPath = L"";
		Window* wnd = ResourceManager::getWindow();
		HWND hwnd = nullptr;
		if (wnd->getName() == "GLFWWindow") {
			HWND hwnd = glfwGetWin32Window(((GLFWWindow*)wnd)->getNativeWindow());
		}
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);

		IFileDialog* pfd;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
			DWORD dwOptions;
			if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
				pfd->SetOptions(dwOptions | FOS_NOCHANGEDIR);
			}
			if (SUCCEEDED(pfd->Show(NULL))) {
				IShellItem* pItem;
				hr = pfd->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						outFolderPath = pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pfd->Release();
		}
		CoUninitialize();
		return outFolderPath;
	}
	std::vector<std::wstring> PlatformUtils::OpenFilesDialog(const char* filter) {
		std::vector<std::wstring> outFilesPath;
		Window* wnd = ResourceManager::getWindow();
		HWND hwnd = nullptr;
		if (wnd->getName() == "GLFWWindow") {
			HWND hwnd = glfwGetWin32Window(((GLFWWindow*)wnd)->getNativeWindow());
		}
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);

		IFileOpenDialog* pfd;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
			DWORD dwOptions;
			if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
				pfd->SetOptions(dwOptions | FOS_ALLOWMULTISELECT | FOS_NOCHANGEDIR);
			}
			if (SUCCEEDED(pfd->Show(NULL))) {
				IShellItemArray* pItems;
				hr = pfd->GetResults(&pItems);
				if (SUCCEEDED(hr)) {
					DWORD count;
					hr = pItems->GetCount(&count);
					if (SUCCEEDED(hr)) {
						for (DWORD i = 0; i < count; i++) {
							IShellItem* pItem;
							if (SUCCEEDED(pItems->GetItemAt(i, &pItem))) {
								PWSTR pszFilePath;
								hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

								if (SUCCEEDED(hr)) {
									outFilesPath.push_back(pszFilePath);
									CoTaskMemFree(pszFilePath);
								}
							}
							pItem->Release();
						}
					}
				}
				pItems->Release();
			}
			pfd->Release();
		} 
		CoUninitialize();
		return outFilesPath;
	}
	std::wstring PlatformUtils::OpenFolderDialog(const char* title) {
		std::wstring outFolderPath;
		Window* wnd = ResourceManager::getWindow();
		HWND hwnd = nullptr;
		if (wnd->getName() == "GLFWWindow") {
			HWND hwnd = glfwGetWin32Window(((GLFWWindow*)wnd)->getNativeWindow());
		}
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);

		IFileDialog* pfd;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
			DWORD dwOptions;
			if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
				pfd->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_NOCHANGEDIR);
			}
			if (SUCCEEDED(pfd->Show(NULL))) {
				IShellItem* pItem;
				hr = pfd->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						outFolderPath = (std::wstring)pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pfd->Release();
		}
		CoUninitialize();
		return outFolderPath;
	}
	void PlatformUtils::executeCommand(const std::string& file, const std::string& command) {
		SHELLEXECUTEINFOA see;
		std::string cmd = " /c \"" + command + "\"";
		ZeroMemory(&see, sizeof(see));
		see.cbSize = sizeof(see);
		see.fMask = 0;
		see.lpVerb = "open";
		see.lpFile = file != "" ? file.c_str() : "cmd";
		see.lpParameters = file != "" ? command.c_str() : cmd.c_str();
		see.nShow = SW_SHOWNORMAL;
		ShellExecuteExA(&see);
	}
	void PlatformUtils::executeMultipleCommands(const std::string& file, const std::vector<std::string>& commands, unsigned long& outDone) {
		std::string commandQuery = " /c ";
		commandQuery += "\"";
		for (std::string command : commands) {
			commandQuery += command;
			commandQuery += " && ";
		}
		commandQuery.pop_back();
		commandQuery.pop_back();
		commandQuery.pop_back();
		commandQuery.pop_back();
		commandQuery += "\"";

		VO_CORE_INFO(commandQuery);
		ShellExecuteA(NULL, "open", "cmd",
			commandQuery.c_str(), 0, SW_SHOWNORMAL);
	}
}
#endif