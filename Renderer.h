#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Errors.h"

class Renderer
{
public:
	Renderer();

	const char* VertexShader =
		"																				\n\
		#version 460																	\n\
																						\n\
		layout (location = 0) in vec3 pos;												\n\
																						\n\
		uniform float TranslationX;														\n\
		uniform float TranslationY;														\n\
		uniform float TranslationZ;														\n\
		uniform float ScaleX;															\n\
		uniform float ScaleY;															\n\
		uniform float ScaleZ;															\n\
																						\n\
		void main()																		\n\
		{																				\n\
			gl_Position = vec4															\n\
			(																			\n\
				ScaleX * pos.x + TranslationX,											\n\
				ScaleY * pos.y + TranslationY,											\n\
				ScaleZ * pos.z + TranslationZ,											\n\
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

	unsigned int vao{ 0 };
	unsigned int vbo{ 0 };
	unsigned int shaderProgram{ 0 };
	unsigned int uniformXMove{ 0 };
	
	unsigned int UniformTranslationX{ 0 };
	unsigned int UniformTranslationY{ 0 };
	unsigned int UniformTranslationZ{ 0 };

	unsigned int UniformScaleX{ 0 };
	unsigned int UniformScaleY{ 0 };
	unsigned int UniformScaleZ{ 0 };

	float OffsetUniformTranslationX{ 0.f };
	float OffsetUniformTranslationY{ 0.f };
	float OffsetUniformTranslationZ{ 0.f };

	float OffsetUniformScaleX = 0.05f;
	float OffsetUniformScaleY = 0.05f; 
	float OffsetUniformScaleZ = 0.05f;

	float OffsetUniformTranslationXLimit{ 1.f };
	float OffsetUniformTranslationYLimit{ 1.f };
	float OffsetUniformTranslationZLimit{ 1.f };

	float UniformStep = 0.01f;

	bool UniformDirectionX{ false };
	bool UniformDirectionY{ false };
	bool UniformDirectionZ{ false };
	

	int Initialize();
	void Success();
	bool Ready();

	void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType);
	void CompileShaderProgram();
	void CreateTriangle();
	void DrawBuffer(GLFWwindow* AppWindow, GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha);
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