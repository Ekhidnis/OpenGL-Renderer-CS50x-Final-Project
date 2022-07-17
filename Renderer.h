#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Errors.h"

class Renderer
{
public:
	Renderer(GLFWwindow* Window);

	const char* VertexShader =
		"																				\n\
		#version 460																	\n\
																						\n\
		layout (location = 0) in vec3 pos;												\n\
																						\n\
		out vec4 vertexColor;															\n\
																						\n\
		uniform mat4 model;																\n\
		uniform mat4 projection;														\n\
																						\n\
		void main()																		\n\
		{																				\n\
			gl_Position = model * vec4													\n\
			(																			\n\
				pos.x,																	\n\
				pos.y,																	\n\
				pos.z,																	\n\
				1.0																		\n\
			);																			\n\
			vertexColor = vec4(clamp(pos, 0.f, 1.f), 1.f);								\n\
		}																				\n\
	";

	const char* FragmentShader =
	"																					\n\
		#version 460																	\n\
																						\n\
		in vec4 vertexColor;															\n\
																						\n\
		out vec4 color; 																\n\
																						\n\
		void main()																		\n\
		{																				\n\
			color = vertexColor;														\n\
		}																				\n\
	";

	const char* TITLE = "Renderer";
	struct Errors::Status Status = Errors::Default;
	GLFWwindow* AppWindow{ nullptr };

	// shader
	unsigned int vao{ 0 }; // vertex array object
	unsigned int vbo{ 0 }; // vertex buffer object
	unsigned int ebo{ 0 }; // elements buffer object
	unsigned int shaderProgram{ 0 };
	
	// uniforms
	unsigned int UniformModelMatrix{ 0 }; // local space
	unsigned int UniformProjectionMatrix{ 0 }; // view space

	// translation
	const float StepLoc = 0.005f; // Fixed amount of units to translate
	const float OffsetTranslationXLimit = 0.5f;
	const float offsetTranslationYLimit = 0.5f;
	const float offsetTranslationZLimit = 0.5f;

	float offsetTranslationX{ 0.f };
	float offsetTranslationY{ 0.f };
	float offsetTranslationZ{ 0.f };
	bool translationDirectionX{ false };
	bool translationDirectionY{ false };
	bool translationDirectionZ{ false };
	
	// rotation
	const float StepRot = 1.f; // Fixed amount of angle to translate
	const float toRadians = 3.14159265f / 180.f;
	const float offsetRotationLimit = 360.f;

	float offsetRotationAngleX{ 0.f };
	float offsetRotationAngleY{ 0.f };
	float offsetRotationAngleZ{ 0.f };

	// scale
	const float StepScale = 0.05f; // Fixed amount of units to scale
	float offsetScaleX = 0.2f;
	float offsetScaleY = 0.2f;
	float offsetScaleZ = 0.2f;
	bool scaleDirectionX{ false };
	bool scaleDirectionY{ false };
	bool scaleDirectionZ{ false };


	// initialization
	int Initialize();
	void Success();
	bool Ready();

	// getters
	int GetStatusID();
	std::string GetStatusText();

	// uniforms
	void GetUniformLocations(int ShaderProgram);
	void UpdateUniforms();
	void AssignUniforms();

	// rendering
	void EnableFeatures();
	void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType);
	void CompileShaderProgram();
	void CreatePyramid();
	void DrawBuffer();
	void UseProgram();

	// validation
	bool CheckShader(unsigned int Shader, GLenum ShaderType);
	bool LinkProgram(unsigned int shaderProgram);
	bool ValidateProgram(unsigned int shaderProgram);
	
};