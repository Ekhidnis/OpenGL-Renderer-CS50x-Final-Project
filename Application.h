#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
public:	
	Application();

protected:
	GLFWwindow* AppWindow;
	const GLint WIDTH = 1280;
	const GLint HEIGHT = 720;
	const char* TITLE = "Ekhidnis' OpenGL Renderer";
	const GLint OpenGLVersionMajor = 4;
	const GLint OpenGLVersionMinor = 6;
	const bool bOpenGLUseExperimental = GL_TRUE;
	const bool bOpenGLAllowForwardCompat = GL_TRUE;
	int bufferWidth{ 0 };
	int bufferHeight{ 0 };
	GLint InitStatus{ 0 };

public:
	void InitGLFW();
	void InitGLEW();
	void MakeWindow();
	void SetParameters();
	void SetBuffer();
	int GetInitStatus();
	void Finalize();
};
