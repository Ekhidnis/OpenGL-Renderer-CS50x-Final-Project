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
	
	static Status ApplicationSuccess{ 11, "Application created succesfully." };
	static Status ApplicationNotInit{ 10, "Application is not ready." };
	static Status ApplicationFail{ -1, "Application failed." };
	
	static Status RendererSuccess{ 21, "Renderer created succesfully." };
	static Status RendererNotInit{ 20, "Renderer is not ready." };
	static Status RendererFail{ -2, "Renderer failed." };
}
