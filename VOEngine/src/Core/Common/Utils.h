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

    static const std::string ReadFile(const std::filesystem::path& path) {
		constexpr auto read_size = std::size_t(4096);
		auto stream = std::ifstream(path.string());
		stream.exceptions(std::ios_base::badbit);

		auto out = std::string();
		auto buf = std::string(read_size, '\0');
		while (stream.read(&buf[0], read_size)) {
			out.append(buf, 0, stream.gcount());
		}
		out.append(buf, 0, stream.gcount());
		return out;
    }

	static const std::vector<std::string> Split(std::string text, const std::string& delimeter) {
		std::vector<std::string> list;
		while (text.find(delimeter, 0) != std::string::npos) {
			size_t pos = text.find(delimeter, 0);
			list.emplace_back(text.substr(0, pos));
			text = text.substr(pos + 1);
		}
		list.emplace_back(text);
		return list;
	}
	static const std::vector<std::wstring> Split(std::wstring text, const std::wstring& delimeter) {
		std::vector<std::wstring> list;
		while (text.find(delimeter, 0) != std::string::npos) {
			size_t pos = text.find(delimeter, 0);
			list.emplace_back(text.substr(0, pos));
			text = text.substr(pos + 1);
		}
		list.emplace_back(text);
		return list;
	}
}