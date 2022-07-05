#include "Renderer.h"

Renderer::Renderer()
{
	CompileShaders();
	CreateTriangle();
};

void Renderer::AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
	unsigned int Shader = glCreateShader(ShaderType);

	const char* ShaderCode_[1];
	ShaderCode_[0] = ShaderCode;

	int ShaderCodeLength[1];
	ShaderCodeLength[0] = strlen(ShaderCode);

	glShaderSource(Shader, 1, ShaderCode_, ShaderCodeLength);
	glCompileShader(Shader);

	if (!CheckShader(Shader, ShaderType)) { return; }

	glAttachShader(ShaderProgram, Shader);
};

void Renderer::CompileShaders()
{
	shaderProgram = glCreateProgram();

	if (!shaderProgram)
	{
		std::cout << "CompileShaders failed. Couldn't create program.\n";
		return;
	};

	AddShader(shaderProgram, VertexShader, GL_VERTEX_SHADER);
	AddShader(shaderProgram, FragmentShader, GL_FRAGMENT_SHADER);

	glLinkProgram(shaderProgram);
	if (!CheckProgramLink()) 
	{ return; };

	glValidateProgram(shaderProgram);
	if (!CheckProgramValidation()) 
	{ return; };

};

void Renderer::CreateTriangle()
{
	float triangle[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.0f, 0.f,
		0.f, 1.f, 0.f
	};

	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

		// VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// content
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
};

void Renderer::UseProgram()
{
	glUseProgram(shaderProgram);

		glBindVertexArray(vao);

			glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

	glUseProgram(0);

};

bool Renderer::CheckShader(unsigned int Shader, GLenum ShaderType)
{
	int result{ 0 };
	char eLog[1024]{ 0 };
	
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		std::cout << "AddShader failed. Couldn't compile " << ShaderType << " program. " << eLog << std::endl;
		
		return false;
	};

	return true;
};

bool Renderer::CheckProgramLink()
{
	int result{ 0 };
	char eLog[1024]{ 0 };
	
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaders failed. Couldn't link program. " << eLog << std::endl;

		return false;
	};

	return true;
}

bool Renderer::CheckProgramValidation()
{
	int result{ 0 };
	char eLog[1024]{ 0 };

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaders failed. Couldn't validate program. " << eLog << std::endl;

		return false;
	};
	return true;
}

void Renderer::DrawBuffer(GLFWwindow* AppWindow, GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha)
{
	glClearColor(Red, Green, Blue, Alpha); // Clear window and set background color
	glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer

	UseProgram();

	glfwSwapBuffers(AppWindow); // Swaps drawed buffer to the window you can see
};