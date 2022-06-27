#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int main()
{
	Application* App = new Application;

	while (App->GetInitStatus() == 0)
	{
		// Initialization
		App->InitGLFW();
		App->MakeWindow();
		App->InitGLEW();
		App->SetParameters();
		App->SetBuffer();
		

		break;
	}

	// Cleanup and exit
	int result = App->GetInitStatus();
	App->Finalize();
	delete(App);
	return result;
}