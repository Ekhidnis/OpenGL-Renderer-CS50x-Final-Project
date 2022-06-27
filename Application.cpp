#include "Application.h"

// Constructor
Application::Application()
{
	InitStatus = -1; // Application is not initialized
};

// -1 : Not Initialized
// 0 : Initialized
// 1 : Failed InitGLFW
// 2 : Failed MakeWindow
// 3 : Failed InitGLEW
int Application::Initialize()
{
	if (InitStatus == -1) { InitGLFW(); }
	if (InitStatus == -1) { MakeWindow(); }
	if (InitStatus == -1) { InitGLEW(); }
	if (InitStatus == -1) { Complete(); }
	return InitStatus;
};

void Application::Setup()
{
	SetParameters();
	SetBuffer();
	SetContext();
	SetViewportSize();
}

// Initializes GLFW framework
void Application::InitGLFW()
{
	if (!glfwInit() )
	{
		InitStatus = 1;
		fprintf(stdout, "%s: glfwInit failed, something is seriously wrong. (%i)\n", TITLE, InitStatus);
		Finalize();
	}
};

// Makes GLFW window
void Application::MakeWindow()
{
	AppWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!AppWindow)
	{
		InitStatus = 2;
		fprintf(stdout, "%s: glfwCreateWindow failed. (%i)\n", TITLE, InitStatus);
		Finalize();
	}
};

// Initializes GLEW interface with GLFW window
void Application::InitGLEW()
{
	// Init GLEW
	if (!glewInit())
	{
		InitStatus = 3;
		fprintf(stdout, "%s: glewInit failed, something is seriously wrong. (%i)\n", TITLE, InitStatus);
		Finalize();
	}
	if (!GLEW_EXT_framebuffer_object) {}; // This will automatically call an exception if the extension does not exist
};

// Sets OpenGL parameters
void Application::SetParameters()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, bOpenGLAllowForwardCompat); // Allows forward compatibility 
	glewExperimental = bOpenGLUseExperimental; // Is advised to include in case developer wants to use any new features
};

// Sets buffer in window
void Application::SetBuffer()
{
	glfwGetFramebufferSize(AppWindow, &bufferWidth, &bufferHeight);
};

// Sets context for GLEW to use 
void Application::SetContext()
{
	glfwMakeContextCurrent(AppWindow);
}

// Sets viewport size
void Application::SetViewportSize()
{
	glViewport(0, 0, bufferWidth, bufferHeight);
};

// Returns current InitStatus
int Application::GetInitStatus()
{
	return InitStatus;
};

GLFWwindow* Application::GetAppWindow()
{
	return AppWindow;
}

// Cleans up 
void Application::Finalize()
{
	glfwDestroyWindow(AppWindow);
	glfwTerminate();
};

void Application::Complete()
{
	InitStatus = 0;
	fprintf(stdout, "%s: Succesfully initialized. (%i)\n", TITLE, InitStatus);
};

void Application::DrawBuffer(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha)
{
	glClearColor(Red, Green, Blue, Alpha); // Clear window and set background color
	glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
	glfwSwapBuffers(AppWindow); // Swaps drawed buffer to the window you can see
}