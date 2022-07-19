#pragma once

#include <chrono>
#include <string>
#include <iostream>

#define sclock std::chrono::steady_clock // can't be changed during runtime unlike system_clock

class Statistics
{
public:
	Statistics(std::string name);
	~Statistics();

	std::string name{ "" };
	int framecount{ 0 };
	sclock::time_point time_start, time_end;

	int GetAverageFPS();
	int GetDuration();
};