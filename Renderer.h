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
		uniform float ScaleX;															\n\
		uniform float ScaleY;															\n\
		uniform float ScaleZ;															\n\
																						\n\
		void main()																		\n\
		{																				\n\
			gl_Position = model * vec4													\n\
			(																			\n\
				ScaleX * pos.x,															\n\
				ScaleY * pos.y,															\n\
				ScaleZ * pos.z,															\n\
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

	unsigned int vao{ 0 };
	unsigned int vbo{ 0 };
	unsigned int shaderProgram{ 0 };
	
	unsigned int UniformTranslationModel{ 0 };

	unsigned int UniformScaleX{ 0 };
	unsigned int UniformScaleY{ 0 };
	unsigned int UniformScaleZ{ 0 };

	float OffsetTranslationX{ 0.f };
	float OffsetTranslationY{ 0.f };
	float OffsetTranslationZ{ 0.f };

	float OffsetUniformScaleX = 0.1f;
	float OffsetUniformScaleY = 0.1f;
	float OffsetUniformScaleZ = 0.1f;

	float OffsetTranslationXMax = 1.f;
	float OffsetTranslationYMax = 1.f;
	float OffsetTranslationZMax = 1.f;

	float UniformStep = 0.01f;

	bool DirectionX{ false };
	bool DirectionY{ false };
	bool DirectionZ{ false };
	

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