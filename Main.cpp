#include "Application.h"
#include "Statistics.h"

int main()
{
	Statistics Application_Statistics ((char*)"Application");
	Application Application_;
	if (Application_.GetInitStatus() != 0)
	{
		return 1;
	}

	// main loop
	while (!glfwWindowShouldClose(Application_.GetAppWindow()))
	{
		glfwPollEvents();
		Application_.DrawBuffer(0.25f, 0, 0.5f, 0.5f);
	};

	return 0;
};

