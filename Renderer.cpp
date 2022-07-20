#include "Renderer.hpp"
#define NotInit Status.id == Errors::RendererNotInit.id


Renderer::Renderer(GLFWwindow* GLFWwindow_)
{
	Window = GLFWwindow_;

	static Shader VertexShader(PATH_SHADER_VERTEX);
	static Shader FragmentShader(PATH_SHADER_FRAGMENT);
	vertexShader = &VertexShader;
	fragmentShader = &FragmentShader;

	if (Window) { Initialize(); }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* CALLBACKS *//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void callback_windowsize(GLFWwindow* window, int width, int height)
{
	glfwSetWindowSize(window, width, height);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* INITIALIZATION *////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Renderer::Initialize()
{
	if (NotInit) { EnableFeatures(); };
	if (NotInit) { CreatePyramid(); };
	if (NotInit) { CompileShaderProgram(); };
	if (NotInit) { Success(); };
	
	return Status.id;
}

void Renderer::AdjustViewport()
{
	glfwGetFramebufferSize(Window, &windowWidth, &windowHeight);

	windowAspectRatio = (float)windowWidth / (float)windowHeight;

	glViewport(0, 0, windowWidth, windowHeight);
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
	uniformModelMatrix = glGetUniformLocation(ShaderProgram, "model");
	uniformProjectionMatrix = glGetUniformLocation(ShaderProgram, "projection");
}

void Renderer::UpdateUniforms()
{
	// translation
		// x
		if (translationDirectionX)
		{
			offsetTranslationX += STEP_LOC;
		}
		else
		{
			offsetTranslationX -= STEP_LOC;
		}
		if (abs(offsetTranslationX) >= OFFSET_TRANSLATION_LIMIT_X)
		{
			translationDirectionX = !translationDirectionX;
		}

	// rotation
		offsetRotationAngleZ += STEP_ROT;
		if (offsetRotationAngleZ >= OFFSET_ROTATION_LIMIT)
		{
			offsetRotationAngleZ -= OFFSET_ROTATION_LIMIT;
		}
}

void Renderer::AssignUniforms()
{
	// projection matrix
	glm::mat4 projection = glm::perspective(FIELD_OF_VIEW, windowAspectRatio, FRUSTRUM_PLANE_NEAR, FRUSTRUM_PLANE_FAR);

	glUniformMatrix4fv(uniformProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projection));
	
	// model matrix
	glm::mat4 model{ 1.f };

	model = glm::translate(model, glm::vec3(offsetTranslationX, offsetTranslationY, offsetTranslationZ));
	model = glm::rotate(model, offsetRotationAngleZ * TO_RADIANS, glm::vec3(1.f, 1.f, 1.f));
	model = glm::scale(model, glm::vec3(offsetScaleX, offsetScaleY, offsetScaleZ));
	
	glUniformMatrix4fv(uniformModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////* RENDERING *//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::EnableFeatures()
{
	glEnable(GL_DEPTH_TEST);
};

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

	if (NotInit) { AddShader(shaderProgram, vertexShader->shader.c_str(), GL_VERTEX_SHADER); }
	if (NotInit) { AddShader(shaderProgram, fragmentShader->shader.c_str(), GL_FRAGMENT_SHADER); }
	if (NotInit) { LinkProgram(shaderProgram); }
	if (NotInit) { ValidateProgram(shaderProgram); }
	if (NotInit) { GetUniformLocations(shaderProgram);  }
}

void Renderer::CreatePyramid()
{
	unsigned int elements[] = {
		0, 3, 1,
		3, 2, 1, 
		2, 1, 0,
		3, 2, 0

	};
	
	float pyramid[] = {
		-1.f, -1.f, 0.f, // 0 close left bottom
		0.f, 0.f, 1.f, // 1 far center bottom
		1.f, -1.0f, 0.f, // 2 close right bottom
		0.f, 1.f, 0.f // 3 center top
	};

	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

		// ebo
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		// vbo
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// content
			glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
			glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // It's important to unbind EBO after unbinding VAO
}

void Renderer::UseProgram()
{
	glUseProgram(shaderProgram);
	
	AssignUniforms();

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

			glDrawElements(GL_TRIANGLES, 3 * 4, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);

}

void Renderer::DrawBuffer()
{
	AdjustViewport();
	UpdateUniforms();
	
	glClearColor(0.f, 0.f, 0.f, 0.f); // Clear window and set background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer

	UseProgram();

	glfwSwapBuffers(Window); // Swaps drawed buffer to the window you can see
	glfwSetWindowSizeCallback(Window, callback_windowsize);
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
		std::cout << "AddShader failed. Couldn't compile " << ShaderType << " program. \n" << eLog << std::endl;
		
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
		std::cout << "CompileShaderProgram failed. Couldn't link program. \n" << eLog << std::endl;

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
		std::cout << "CompileShaderProgram failed. Couldn't validate program. \n" << eLog << std::endl;

		return false;
	};
	return true;
}