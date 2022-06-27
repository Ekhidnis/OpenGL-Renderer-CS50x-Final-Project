#include "Application.h"

// Constructor
Application::Application()
{
}

// Initializes GLFW framework
void Application::InitGLFW()
{
	if (!glfwInit())
	{
		fprintf(stdout, "ERROR #1: glfwInit failed, something is seriously wrong.");
		Finalize();
		InitStatus = 1;
	}
};

// Makes GLFW window
void Application::MakeWindow()
{
	AppWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!AppWindow)
	{
		fprintf(stdout, "ERROR #2: glfwCreateWindow failed.");
		Finalize();
		InitStatus = 2;
	}
}

// Initializes GLEW interface with GLFW window
void Application::InitGLEW()
{
	// Init GLEW
	if (!glewInit())
	{
		fprintf(stdout, "ERROR #3: glewInit failed, something is seriously wrong.");
		Finalize();
		InitStatus = 3;
	}
	if (!GLEW_EXT_framebuffer_object) {}; // This will automatically call an exception if the extension does not exist
}


// Sets OpenGL parameters
void Application::SetParameters()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, bOpenGLAllowForwardCompat); // Allows forward compatibility 
	glewExperimental = bOpenGLUseExperimental; // Is advised to include in case developer wants to use any new features
}

void Application::SetBuffer()
{
	glfwGetFramebufferSize(AppWindow, &bufferWidth, &bufferHeight);
}

int Application::GetInitStatus()
{
	return InitStatus;
}

void Application::Finalize()
{
	glfwDestroyWindow(AppWindow);
	glfwTerminate();
}