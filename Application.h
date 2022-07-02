#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Errors.h"

/* OpenGL application using GLEW/GLFW */
class Application
{
public:	
	Application();
	~Application();

private:
	struct Errors::Status Status = Errors::Default;
	GLFWwindow* AppWindow{ nullptr };
	const GLint WIDTH = 1280;
	const GLint HEIGHT = 720;
	const char* TITLE = "Ekhidnis' OpenGL Renderer";
	const GLint OpenGLVersionMajor = 4;
	const GLint OpenGLVersionMinor = 6;
	const bool bOpenGLUseExperimental = GL_TRUE;
	const bool bOpenGLAllowForwardCompat = GL_TRUE;
	int bufferWidth{ 0 };
	int bufferHeight{ 0 };
	
public:
	int Initialize();
	void InitGLFW();
	void InitGLEW();

	void SetDefaults();
	void SetGLFWParameters();
	void SetGLEWParameters();
	void SetGLFWBuffer();
	void SetGLFWContext();
	void SetViewportSize();

	bool Ready();
	int GetStatusID();
	std::string GetStatusText();
	GLFWwindow* GetAppWindow();

	void Success();
	void Finalize();

	void MakeWindow();
	void DrawBuffer(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Alpha);
};
