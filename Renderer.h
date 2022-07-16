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
		uniform mat4 model;																\n\
		void main()																		\n\
		{																				\n\
			gl_Position = model * vec4													\n\
			(																			\n\
				pos.x,																	\n\
				pos.y,																	\n\
				pos.z,																	\n\
				1.0																		\n\
			);																			\n\
		}																				\n\
	";

	const char* FragmentShader =
	"																					\n\
		#version 460																	\n\
																						\n\
		out vec4 color; 																\n\
																						\n\
		void main()																		\n\
		{																				\n\
			color = vec4(1.0, 1.0, 1.0, 1.0);											\n\
		}																				\n\
	";

	const char* TITLE = "Renderer";
	struct Errors::Status Status = Errors::Default;
	GLFWwindow* AppWindow{ nullptr };

	const float toRadians = 3.14159265f / 180.f;
	const float uniformStep = 0.01f;

	unsigned int vao{ 0 };
	unsigned int vbo{ 0 };
	unsigned int shaderProgram{ 0 };
	
	unsigned int UniformTranslationModel{ 0 };

	float offsetTranslationX{ 0.f };
	float offsetTranslationY{ 0.f };
	float offsetTranslationZ{ 0.f };

	float OffsetTranslationXLimit = 1.f;
	float offsetTranslationYLimit = 1.f;
	float offsetTranslationZLimit = 1.f;

	bool translationDirectionX{ false };
	bool translationDirectionY{ false };
	bool translationDirectionZ{ false };

	float offsetRotationAngleX{ 0.f };
	float offsetRotationAngleY{ 0.f };
	float offsetRotationAngleZ{ 0.f };

	float offsetScaleX = 0.1f;
	float offsetScaleY = 0.1f;
	float offsetScaleZ = 0.1f;

	float offsetScaleXLimit = 0.3f;
	float offsetScaleYLimit = 0.3f;
	float offsetScaleZLimit = 0.3f;

	bool scaleDirectionX{ false };
	bool scaleDirectionY{ false };
	bool scaleDirectionZ{ false };


	

	int Initialize();
	void Success();
	bool Ready();

	void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType);
	void CompileShaderProgram();
	void CreateTriangle();
	void DrawBuffer();
	void UseProgram();

	void GetUniformLocations(int ShaderProgram);
	void UpdateUniforms();
	void AssignUniforms();

	int GetStatusID();
	std::string GetStatusText();
	
	bool CheckShader(unsigned int Shader, GLenum ShaderType);
	bool LinkProgram(unsigned int shaderProgram);
	bool ValidateProgram(unsigned int shaderProgram);
	
};