#include "Renderer.h"
#define NotInit Status.id == Errors::RendererNotInit.id


Renderer::Renderer(GLFWwindow* Window)
{
	Status = Errors::RendererNotInit;
	AppWindow = Window;
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
	UniformTranslationModel = glGetUniformLocation(ShaderProgram, "model");
}

void Renderer::UpdateUniforms()
{
	// translation
		// x
		if (translationDirectionX)
		{
			offsetTranslationX += uniformStep;
		}
		else
		{
			offsetTranslationX -= uniformStep;
		}
		if (abs(offsetTranslationX) >= OffsetTranslationXLimit)
		{
			translationDirectionX = !translationDirectionX;
		}

		// y
		if (translationDirectionY)
		{
			offsetTranslationY += uniformStep;
		}
		else
		{
			offsetTranslationY -= uniformStep;
		}
		if (abs(offsetTranslationY) >= offsetTranslationYLimit)
		{
			translationDirectionY = !translationDirectionY;
		}

		// z
		if (translationDirectionZ)
		{
			offsetTranslationZ += uniformStep;
		}
		else
		{
			offsetTranslationZ -= uniformStep;
		}
		if (abs(offsetTranslationZ) >= offsetTranslationZLimit)
		{
			translationDirectionZ = !translationDirectionZ;
		}

	// rotation
		offsetRotationAngleZ += uniformStep * 100.f;
		if (offsetRotationAngleZ >= 360.f)
		{
			offsetRotationAngleZ -= 360.f;
		}

	// scale
		if (scaleDirectionX)
		{
			offsetScaleX += uniformStep;
		}
		else
		{
			offsetScaleX -= uniformStep;
		}
		if (abs(offsetScaleX) >= offsetScaleXLimit)
		{
			scaleDirectionX = !scaleDirectionX;
		}
}

void Renderer::AssignUniforms()
{
	glm::mat4 model{1.f};

	model = glm::translate(model, glm::vec3(offsetTranslationX, offsetTranslationY, offsetTranslationZ));
	model = glm::rotate(model, offsetRotationAngleZ * toRadians, glm::vec3(0.f, 0.f, 1.f));
	model = glm::scale(model, glm::vec3(offsetScaleX, offsetScaleY, offsetScaleZ));
	
	glUniformMatrix4fv(UniformTranslationModel, 1, GL_FALSE, glm::value_ptr(model));
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
	
	AssignUniforms();

		glBindVertexArray(vao);

			glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

	glUseProgram(0);

}

void Renderer::DrawBuffer()
{
	UpdateUniforms();
	
	glClearColor(0.f, 0.f, 0.f, 0.f); // Clear window and set background color
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