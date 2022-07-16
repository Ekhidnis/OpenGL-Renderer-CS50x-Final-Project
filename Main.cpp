#include "Application.h"
#include "Statistics.h"
#include "Renderer.h"

int main()
{	
	Statistics Statistics_("Runtime");
	
	Application Application_;
	if (!Application_.Ready()) { return Application_.GetStatusID(); };

	Renderer Renderer_(Application_.GetAppWindow());
	if (!Renderer_.Ready()) { return Renderer_.GetStatusID(); };


	while (!glfwWindowShouldClose(Application_.GetAppWindow()))
	{
		glfwPollEvents();
		Renderer_.DrawBuffer();
		Statistics_.framecount++;
	};


	return 0;
}
