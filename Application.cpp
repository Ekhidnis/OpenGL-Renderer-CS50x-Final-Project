#include "Application.h"



GLuint vao{0}, vbo{0}, shader{0};

static const char* VertexShader =
"																			\n\
	#version 460															\n\
																			\n\
	layout (location = 0) in vec3 pos;										\n\
																			\n\
	void main()																\n\
	{																		\n\
		float scale = 0.1;													\n\
		gl_Position = vec4(scale * pos.x, scale * pos.y, scale * pos.z, 1.0);\n\
	}																		\n\
";

static const char* FragmentShader =
"																			\n\
	#version 460															\n\
																			\n\
	out vec4 color; 														\n\
																			\n\
	void main()																\n\
	{																		\n\
		color = vec4(1.0, 1.0, 1.0, 1.0);									\n\
	}																		\n\
";

void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
	unsigned int Shader = glCreateShader(ShaderType);

	const char* ShaderCode_[1];
	ShaderCode_[0] = ShaderCode;

	int ShaderCodeLength[1];
	ShaderCodeLength[0] = strlen(ShaderCode);

	glShaderSource(Shader, 1, ShaderCode_, ShaderCodeLength);
	glCompileShader(Shader);

	int result{ 0 };
	char eLog[1024]{ 0 };

	glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "AddShader failed. Couldn't compile " << ShaderType << " shader. " << eLog << std::endl;
		return;
	};

	glAttachShader(ShaderProgram, Shader);
};

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		std::cout << "CompileShaders failed. Couldn't create shader.\n";
		return;
	};

	AddShader(shader, VertexShader, GL_VERTEX_SHADER);
	AddShader(shader, FragmentShader, GL_FRAGMENT_SHADER);

	int result{ 0 };
	char eLog[1024]{ 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaders failed. Couldn't link program. " << eLog << std::endl;
	};

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaders failed. Couldn't validate program. " << eLog << std::endl;
	};

};

void CreateTriangle()
{
	float triangle[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.0f, 0.f,
		0.f, 1.f, 0.f
	};

	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

		// vbo
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// content
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
			glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
};







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* INITIALIZATION *////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Application::Application()
{
	Status = Errors::ApplicationNotInit;

	if (Initialize() == Errors::ApplicationSuccess.id)
	{
		CreateTriangle();
		CompileShaders();
	}
};

Application::~Application()
{
}

int Application::Initialize()
{
	if (Status.id == Errors::ApplicationNotInit.id) { InitGLFW(); }
	SetGLFWParameters();

	if (Status.id == Errors::ApplicationNotInit.id) { MakeWindow(); }
	SetGLFWBuffer();
	SetViewportSize();
	SetGLFWContext();

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

void Application::InitGLEW()
{
	glewExperimental = bOpenGLUseExperimental; // Is advised to include in case developer wants to use any new features
	if (glewInit() != GLEW_OK)
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


void Application::SetGLFWParameters()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, bOpenGLAllowForwardCompat); // Allows forward compatibility
};

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

	glUseProgram(shader);

		glBindVertexArray(vao);

			glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

	glUseProgram(0);

	glfwSwapBuffers(AppWindow); // Swaps drawed buffer to the window you can see
};