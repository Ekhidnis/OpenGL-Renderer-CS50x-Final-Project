#include "Renderer.h"
#define NotInit Status.id == Errors::RendererNotInit.id


Renderer::Renderer()
{
	Status = Errors::RendererNotInit;
	Initialize();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* INITIALIZATION *////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Renderer::Initialize()
{
	if (NotInit) { CreateTriangle(); };
	if (NotInit) { CompileShaderProgram(); };
	if (NotInit) { Success(); };
	
	return Status.id;
}

void Renderer::Success()
{
	Status = Errors::RendererSuccess;
	std::cout << TITLE << ": Succesfully initialized.\n";
}

bool Renderer::Ready()
{
	return Status.id == Errors::RendererSuccess.id;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* GETTERS *////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Renderer::GetStatusID()
{
	return Status.id;
}

std::string Renderer::GetStatusText()
{
	return Status.text;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* UNIFORMS *///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Renderer::GetUniformLocations(int ShaderProgram)
{
	UniformTranslationX = glGetUniformLocation(ShaderProgram, "TranslationX");
	UniformTranslationY = glGetUniformLocation(ShaderProgram, "TranslationY");
	UniformTranslationZ = glGetUniformLocation(ShaderProgram, "TranslationZ");

	UniformScaleX = glGetUniformLocation(ShaderProgram, "ScaleX");
	UniformScaleY = glGetUniformLocation(ShaderProgram, "ScaleY");
	UniformScaleZ = glGetUniformLocation(ShaderProgram, "ScaleZ");
}

void Renderer::UpdateUniforms()
{
	// translation x
	if (UniformDirectionX)
	{
		OffsetUniformTranslationX += UniformStep * 0.7f;
	}
	else
	{
		OffsetUniformTranslationX -= UniformStep * 0.7f;
	}
	if (abs(OffsetUniformTranslationX) >= OffsetUniformTranslationXLimit)
	{
		UniformDirectionX = !UniformDirectionX;
	}

	// translation y
	if (UniformDirectionY)
	{
		OffsetUniformTranslationY += UniformStep * 1.1f;
	}
	else
	{
		OffsetUniformTranslationY -= UniformStep * 1.1f;
	}
	if (abs(OffsetUniformTranslationY) >= OffsetUniformTranslationYLimit)
	{
		UniformDirectionY = !UniformDirectionY;
	}

	// translation z
	if (UniformDirectionZ)
	{
		OffsetUniformTranslationZ += UniformStep * 1.3f;
	}
	else
	{
		OffsetUniformTranslationZ -= UniformStep * 1.3f;
	}
	if (abs(OffsetUniformTranslationZ) >= OffsetUniformTranslationZLimit)
	{
		UniformDirectionZ = !UniformDirectionZ;
	}
}

void Renderer::AssignUniforms()
{
	glUniform1f(UniformTranslationX, OffsetUniformTranslationX);
	glUniform1f(UniformTranslationY, OffsetUniformTranslationY);
	glUniform1f(UniformTranslationZ, OffsetUniformTranslationZ);

	glUniform1f(UniformScaleX, OffsetUniformScaleX);
	glUniform1f(UniformScaleY, OffsetUniformScaleY);
	glUniform1f(UniformScaleZ, OffsetUniformScaleZ);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* RENDERING *//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Renderer::AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
	unsigned int Shader = glCreateShader(ShaderType);

	const char* ShaderCode_[1]{ "" };
	ShaderCode_[0] = ShaderCode;

	int ShaderCodeLength[1]{ 0 };
	ShaderCodeLength[0] = strlen(ShaderCode);

	glShaderSource(Shader, 1, ShaderCode_, ShaderCodeLength);
	glCompileShader(Shader);

	if (!CheckShader(Shader, ShaderType)) 
	{ 
		Status = Errors::RendererFail;
	}

	glAttachShader(ShaderProgram, Shader);
}

void Renderer::CompileShaderProgram()
{
	shaderProgram = glCreateProgram();

	if (!shaderProgram)
	{
		std::cout << "CompileShaderProgram failed. Couldn't create program.\n";
		Status = Errors::RendererFail;
	};

	if (NotInit) { AddShader(shaderProgram, VertexShader, GL_VERTEX_SHADER); }
	if (NotInit) { AddShader(shaderProgram, FragmentShader, GL_FRAGMENT_SHADER); }
	if (NotInit) { LinkProgram(shaderProgram); }
	if (NotInit) { ValidateProgram(shaderProgram); }
	if (NotInit) { GetUniformLocations(shaderProgram);  }
}

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
}

void Renderer::UseProgram()
{
	glUseProgram(shaderProgram);

		glBindVertexArray(vao);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			AssignUniforms();

		glBindVertexArray(0);

	glUseProgram(0);

}

void Renderer::DrawBuffer(GLFWwindow* AppWindow, GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha)
{
	UpdateUniforms();
	
	glClearColor(Red, Green, Blue, Alpha); // Clear window and set background color
	glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer

	UseProgram();

	glfwSwapBuffers(AppWindow); // Swaps drawed buffer to the window you can see
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* VALIDATION */////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
}

bool Renderer::LinkProgram(unsigned int shaderProgram)
{
	int result{ 0 };
	char eLog[1024]{ 0 };
	
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaderProgram failed. Couldn't link program. " << eLog << std::endl;

		return false;
	};

	return true;
}

bool Renderer::ValidateProgram(unsigned int shaderProgram)
{
	int result{ 0 };
	char eLog[1024]{ 0 };

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		std::cout << "CompileShaderProgram failed. Couldn't validate program. " << eLog << std::endl;

		return false;
	};
	return true;
}