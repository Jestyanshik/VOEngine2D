#include "vopch.h"


namespace VOEngine {
	static std::string WideStringToString(const std::wstring& str) {
		std::string buffer(new char[sizeof(str)]);
		wcstombs_s(nullptr, (char *)buffer.c_str(), buffer.length() - 1, str.c_str(), _TRUNCATE);
		return buffer;
	}
}