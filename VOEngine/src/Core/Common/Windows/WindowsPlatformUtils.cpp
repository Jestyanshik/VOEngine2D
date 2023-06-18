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
	COMDLG_FILTERSPEC* CreateFilter(const std::wstring& filter, const std::vector<std::wstring>& extensions) {
		COMDLG_FILTERSPEC* fSpec = nullptr;
		if (extensions.size() % 2 != 0) {
			VO_CORE_WARN("OpenFileDialog Filter was not applied due to uneven amount of extesions and typenames");
		}
		else {
			fSpec = new COMDLG_FILTERSPEC[extensions.size() / 2];
			for (uint32_t i = 0; i < extensions.size(); i += 2) {
				COMDLG_FILTERSPEC filterSpec;
				filterSpec.pszName = extensions[i].c_str();
				filterSpec.pszSpec = extensions[i + 1].c_str();
				fSpec[i / 2] = filterSpec;
			}
		}
		return fSpec;
	}

	//filter consists of name|extensions e.g "Image((*.jpg;*.jpeg)|*.jpg;*.jpeg|Bitmap (*.bmp)|*.bmp" 
	std::wstring PlatformUtils::OpenFileDialog(const std::wstring& filter) {
		std::wstring outFolderPath;
		auto extensions = Split(filter, L"|");
		COMDLG_FILTERSPEC* fSpec = CreateFilter(filter, extensions);
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);

		IFileDialog* pfd;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
			DWORD dwOptions;
			if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
				pfd->SetOptions(dwOptions | FOS_NOCHANGEDIR);
				if (fSpec != nullptr)
					pfd->SetFileTypes(sizeof(*fSpec) / sizeof(COMDLG_FILTERSPEC), fSpec);
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

	//filter consists of name|extensions e.g "Image((*.jpg;*.jpeg)|*.jpg;*.jpeg|Bitmap (*.bmp)|*.bmp" 
	std::vector<std::wstring> PlatformUtils::OpenFilesDialog(const std::wstring& filter) {
		std::vector<std::wstring> outFilesPath;
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		auto extensions = Split(filter, L"|");
		COMDLG_FILTERSPEC* fSpec = CreateFilter(filter, extensions);

		IFileOpenDialog* pfd;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
			DWORD dwOptions;
			if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
				pfd->SetOptions(dwOptions | FOS_ALLOWMULTISELECT | FOS_NOCHANGEDIR);
				if (fSpec != nullptr)
					pfd->SetFileTypes(sizeof(*fSpec) / sizeof(COMDLG_FILTERSPEC), fSpec);
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
}
#endif