#include "Statistics.h"

Statistics::Statistics(char* string_)
{
	name = (char*)string_;
	time_start = sclock::now();
}

Statistics::~Statistics()
{
	time_end = sclock::now();
	fprintf(stdout, "%s lasted for: %i seconds\n", name, GetDuration());
	fprintf(stdout, "%s average FPS: %i\n", name, GetAverageFPS());
}

int Statistics::GetAverageFPS()
{
	return 0;
}

int Statistics::GetDuration()
{
	time_end = sclock::now();
	int duration = std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start).count();

	return duration;
}