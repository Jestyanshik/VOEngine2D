#pragma once
#include "vopch.h"


namespace VOEngine {
	static std::string WideStringToString(const std::wstring& str) {
        std::string strTo;
        char* szTo = new char[str.length() + 1];
        szTo[str.size()] = '\0';
        WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, szTo, (int)str.length(), NULL, NULL);
        strTo = szTo;
        delete[] szTo;
        return strTo;
	}
}