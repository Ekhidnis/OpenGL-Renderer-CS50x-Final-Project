#pragma once

#include <stdio.h>
#include <iostream>

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
		void main()																		\n\
		{																				\n\
			float scale = 0.1;															\n\
			gl_Position = vec4(scale * pos.x, scale * pos.y, scale * pos.z, 1.0);		\n\
		}																				\n\
	";

	const char* FragmentShader =
	"																				\n\
		#version 460																	\n\
																						\n\
		out vec4 color; 																\n\
																						\n\
		void main()																		\n\
		{																				\n\
			color = vec4(1.0, 1.0, 1.0, 1.0);											\n\
		}																				\n\
	";

	unsigned int vao{ 0 };
	unsigned int vbo{ 0 };
	unsigned int shaderProgram{ 0 };
	


	void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType);
	void CompileShaders();
	void CreateTriangle();
	void DrawBuffer(GLFWwindow* AppWindow, GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha);
	void UseProgram();
	

	bool CheckShader(unsigned int Shader, GLenum ShaderType);
	bool CheckProgramLink();
	bool CheckProgramValidation();
	
};