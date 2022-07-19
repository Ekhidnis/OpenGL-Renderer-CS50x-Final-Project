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
	
	static Status WindowSuccess{ 11, "Window created succesfully." };
	static Status WindowNotInit{ 10, "Window is not ready." };
	static Status WindowFail{ -1, "Window failed." };
	
	static Status RendererSuccess{ 21, "Renderer created succesfully." };
	static Status RendererNotInit{ 20, "Renderer is not ready." };
	static Status RendererFail{ -2, "Renderer failed." };
}
