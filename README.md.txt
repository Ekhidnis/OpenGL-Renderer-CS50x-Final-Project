# Ekhidnis' OpenGL Renderer (CS50x Final Project)
#### Video Demo:  <URL HERE>
#### Description: Small-scale renderer made using OpenGL libraries on top of C++ language.

## The Goal
I understand and feel guilty that my project is not trying to bring anything useful to the world, but I can't withstand the urge to invest my time into learning engines and graphics, because it lights the fire in my eyes.

## Technical stack
OpenGL - Open Graphics Library;

GLEW - OpenGL Extension Wrangler which is an extensions manager and an interface for OpenGL.
	To use GLEW we should include header (#include <GL/glew.h>);
	To access the latest features of OpenGL we should set variable experimental mode to true (glewExperimental = GL_TRUE);
	Then we need to initialize the interface and check if the initialization was successful:
		if (!glewInit())
		{
			fprintf(stdout, "glewInit failed, something is seriously wrong.");
		}
	Check if your extensions exist
		if (!GLEW_EXT_framebuffer_object){} // This will automatically call an exception if the extension does not exist

GLFW - I couldn't find what the abbreviature stands for. GLFW OpenGL library that is specifically made for managing windows and input. (I choose this as a lightweight and simple alternative to SDL since I'm planning a small-scale project with no audio and other features SDL provides)
	To use GLFW we should include header (#include <GLFW/glfw3.h>)
	Then we need to initialize it and check if the initialization was successful:
		if (!glfwInit())
		{
			fprintf(stdout, "glfwInit failed, something is seriously wrong.");
			glfwTerminate(); // If anything is initialized we should terminate it since the error appeared
		}

## What I have learned
Implementing libraries

## Error codes
1 - glfwInit failed
2 - glfwCreateWindow failed
3 - glewInit failed