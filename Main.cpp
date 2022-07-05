#include "Application.h"
#include "Statistics.h"
#include "Renderer.h"

int main()
{	
	Statistics Statistics_("Runtime");
	Application Application_;
	Renderer Renderer_;

	if (!Application_.Ready()) { return Application_.GetStatusID(); };

	while (!glfwWindowShouldClose(Application_.GetAppWindow()))
	{
		glfwPollEvents();
		Renderer_.DrawBuffer(Application_.GetAppWindow(), 0.25f, 0, 0.5f, 0.5f);
		Statistics_.framecount++;
	};

	return 0;
};

