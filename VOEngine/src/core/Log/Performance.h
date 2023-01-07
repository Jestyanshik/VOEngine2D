#pragma once
#include "vopch.h"

#ifdef PROFILING
#define timeit() Timer t(__FUNCTION__)
#endif


class Timer {
public:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::string FunctionName;

	Timer(const std::string& fName) {
		FunctionName = fName;
		start = std::chrono::steady_clock::now();
	}
	~Timer() {
		end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		VO_CORE_INFO("Elapsed time: {} in function {}", elapsed_seconds, FunctionName);
	}

};