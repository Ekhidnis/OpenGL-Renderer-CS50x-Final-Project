#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Errors.hpp"

/* OpenGL application using GLEW/GLFW */
class Window
{
public:
	Window();

private:
	struct Errors::Status Status = Errors::Default;
	GLFWwindow* glfwWindow{ nullptr };
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const char* TITLE = "Ekhidnis' OpenGL Engine";
	const int OpenGLVersionMajor = 4;
	const int OpenGLVersionMinor = 6;
	const bool bOpenGLUseExperimental = GL_TRUE;
	const bool bOpenGLAllowForwardCompat = GL_TRUE;
	int bufferWidth{ 0 };
	int bufferHeight{ 0 };

public:
	int Initialize();
	void InitGLFW();
	void InitGLEW();

	void SetGLFWParameters();
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
};
