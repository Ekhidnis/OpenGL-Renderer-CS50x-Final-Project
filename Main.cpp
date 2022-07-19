#include "Window.hpp"
#include "Statistics.hpp"
#include "Renderer.hpp"


void callback_windowsize(GLFWwindow* window, int width, int height)
{
	glfwSetWindowSize(window, width, height);
}

int main()
{	
	Statistics StatsRuntime_("Runtime");
	
	Window Window_;
	if (!Window_.Ready()) { return Window_.GetStatusID(); };

	Renderer Renderer_(Window_.GetAppWindow());
	if (!Renderer_.Ready()) { return Renderer_.GetStatusID(); };


	while (!glfwWindowShouldClose(Window_.GetAppWindow()))
	{
		Renderer_.DrawBuffer();
		StatsRuntime_.framecount++;


		glfwPollEvents();
		glfwSetWindowSizeCallback(Window_.GetAppWindow(), callback_windowsize);
	};


	return 0;
}
