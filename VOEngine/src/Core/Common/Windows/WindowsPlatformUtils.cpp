#include "vopch.h"
#ifdef _WIN32
#include "../PlatformUtils.h"
#include "../Utils.h"
#include "Core/ResourceManager.h"
#include "Core/Window/GLFWWindow/GLFWWindow.h"

#include <commdlg.h>
#include <shobjidl_core.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace VOEngine {
	std::thread PlatformUtils::m_CommandThread, PlatformUtils::m_LoopThread;
	bool PlatformUtils::s_StopExecution;

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
		if (!m_CommandThread.joinable()) {
			m_CommandThread = std::thread([file, command]() {
				system(command.c_str());
			});
		}
	}
	void PlatformUtils::executeMultipleCommands(const std::string& file, const std::vector<std::string>& commands) {
		if (s_StopExecution) {
			try {
				m_LoopThread.join();
			}
			catch (const std::exception&) {}
			s_StopExecution = false;
		}
		m_LoopThread = std::thread([file, commands]() {
			for (const std::string& command : commands) {
				if (s_StopExecution) {
					break;
				}
				VO_CORE_INFO(command);
				m_CommandThread = std::thread([file, command]() {
					system(command.c_str());
				});
				m_CommandThread.join();
			}
		});
	}
}
#endif