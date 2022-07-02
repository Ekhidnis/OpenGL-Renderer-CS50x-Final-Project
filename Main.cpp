#include "Application.h"
#include "Statistics.h"

int main()
{
	Statistics Stats_Application("Application");
	Application Application_;

	if (!Application_.Ready()) { return Application_.GetStatusID(); };

	while (!glfwWindowShouldClose(Application_.GetAppWindow()))
	{
		glfwPollEvents();
		Application_.DrawBuffer(0.25f, 0, 0.5f, 0.5f);
		Stats_Application.framecount++;
	};

	return 0;
};

