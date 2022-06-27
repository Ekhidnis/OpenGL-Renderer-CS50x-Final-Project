#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int framecount{ 0 };

int cleanup(Application* App, int InitStatus)
{
	App->Finalize();
	delete(App);
	return InitStatus;
};

int main()
{
	glGetString(GL_VENDOR);
	glGetString(GL_RENDERER);
	glGetString(GL_VERSION);
	// Make app and init
	Application* App = new Application;
	if (App->Initialize() != 0)
	{
		return cleanup(App, App->GetInitStatus());
	};

	// Set settings
	App->Setup();

	// Main loop
	while (!glfwWindowShouldClose(App->GetAppWindow()))
	{
		glfwPollEvents(); // Get events

		// Draw
		App->DrawBuffer(0.25f, 0, 0.5f, 0.5f);
		framecount++;
	};

	printf("%i", framecount);
	return cleanup(App, App->GetInitStatus());
};

