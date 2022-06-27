#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int cleanup(Application* App, int InitStatus)
{
	App->Finalize();
	delete(App);
	return InitStatus;
};

int main()
{
	// Make an application
	Application* App = new Application;
	if (App->Initialize() != 0)
	{
		return cleanup(App, App->GetInitStatus());
	};

	return cleanup(App, App->GetInitStatus());
};

