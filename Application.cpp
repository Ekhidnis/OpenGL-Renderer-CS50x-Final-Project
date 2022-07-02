#include "Application.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* INITIALIZATION *////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Application::Application()
{
	Status = Errors::ApplicationNotInit;
	Initialize();
	SetDefaults();
};

Application::~Application()
{
}

int Application::Initialize()
{
	if (Status.id == Errors::ApplicationNotInit.id) { InitGLFW(); }
	if (Status.id == Errors::ApplicationNotInit.id) { MakeWindow(); }
	if (Status.id == Errors::ApplicationNotInit.id) { InitGLEW(); }
	if (Status.id == Errors::ApplicationNotInit.id) { Success(); }
	return Status.id;
};

void Application::InitGLFW()
{
	if (!glfwInit() )
	{
		Status = Errors::ApplicationFail;
		std::cout << TITLE << ": glfwInit failed.\n";
		Finalize();
	}
};

// Initializes GLEW interface with GLFW window
void Application::InitGLEW()
{
	// Init GLEW
	if (!glewInit())
	{
		Status = Errors::ApplicationFail;
		std::cout << TITLE << ": glewInit failed.\n";
		Finalize();
	}
	if (!GLEW_EXT_framebuffer_object) {}; // This will automatically call an exception if the extension does not exist
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* SETTERS *////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Application::SetDefaults()
{
	SetGLFWParameters();
	SetGLFWBuffer();
	SetGLFWContext();
	SetViewportSize();
}

void Application::SetGLFWParameters()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, bOpenGLAllowForwardCompat); // Allows forward compatibility 
};

void Application::SetGLEWParameters()
{
	glewExperimental = bOpenGLUseExperimental; // Is advised to include in case developer wants to use any new features
}

void Application::SetGLFWBuffer()
{
	glfwGetFramebufferSize(AppWindow, &bufferWidth, &bufferHeight);
};

void Application::SetGLFWContext()
{
	glfwMakeContextCurrent(AppWindow);
}

void Application::SetViewportSize()
{
	glViewport(0, 0, bufferWidth, bufferHeight);
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* GETTERS *////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Application::Ready()
{
	return Status.id == Errors::ApplicationSuccess.id;
}

int Application::GetStatusID()
{
	return Status.id;
};

std::string Application::GetStatusText()
{
	return Status.text;
};

GLFWwindow* Application::GetAppWindow()
{
	return AppWindow;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////* FINALIZATION *////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Application::Finalize()
{
	std::cout << GetStatusText() << "\n";
	glfwDestroyWindow(AppWindow);
	glfwTerminate();
};

void Application::Success()
{
	Status = Errors::ApplicationSuccess;
	std::cout << TITLE << ": Succesfully initialized.\n";
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////* RENDERING *////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Application::MakeWindow()
{
	AppWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!AppWindow)
	{
		Status = Errors::ApplicationFail;
		std::cout << TITLE << ": glfwCreateWindow failed.\n";
		Finalize();
	}
};

void Application::DrawBuffer(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha)
{
	glClearColor(Red, Green, Blue, Alpha); // Clear window and set background color
	glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
	glfwSwapBuffers(AppWindow); // Swaps drawed buffer to the window you can see
}