#include "Window.hpp"
#include "Statistics.hpp"
#include "Renderer.hpp"

int main()
{	
	Statistics StatsRuntime_("Runtime");
	
	Window Window_;
	if (!Window_.Ready()) { return Window_.GetStatusID(); };
	GLFWwindow* MainWindow = Window_.GetAppWindow();

	Renderer Renderer_(MainWindow);
	if (!Renderer_.Ready()) { return Renderer_.GetStatusID(); };

	

	while (!glfwWindowShouldClose(MainWindow))
	{
		Renderer_.DrawBuffer();
		StatsRuntime_.framecount++;


		glfwPollEvents();
	};


	return 0;
}
