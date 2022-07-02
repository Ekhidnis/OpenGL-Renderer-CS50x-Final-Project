#pragma once

#include <string>

namespace Errors
{
	struct Status
	{
		int id;
		std::string text;
	};

	static Status Default{ 0, "" };
	static Status ApplicationSuccess{ 101, "Application created succesfully." };
	static Status ApplicationNotInit{ 100, "Application is not initialized." };
	static Status ApplicationFail{ -102, "Application failed." };
}
