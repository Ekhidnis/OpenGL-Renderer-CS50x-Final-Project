#pragma once

#include <chrono>

#define sclock std::chrono::steady_clock // can't be changed during runtime unlike system_clock

class Statistics
{
public:
	Statistics(char* name);
	~Statistics();

	char* name{ nullptr };
	int framecount{ 0 };
	sclock::time_point time_start, time_end;

	int GetAverageFPS();
	int GetDuration();
};