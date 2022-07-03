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
	Then we need to initialize the interface and check if the initialization was successful;

GLFW - I couldn't find what the abbreviature stands for. GLFW OpenGL library that is specifically made for managing windows and input. (I choose this as a lightweight and simple alternative to SDL since I'm planning a small-scale project with no audio and other features SDL provides)
	To use GLFW we should include header (#include <GLFW/glfw3.h>)
	Then we need to initialize it and check if the initialization was successful;

## What it can do at the moment
Create and initialize application (initializes opengl stack and operates created window)
Create and initialize statistics (has timer and fps counter)
Has Errors namespace where types of errors are declared and used throughout the code
Draws triangle

## What aspects I had to invest my time in and gain knowledge about
Implementing libraries
GLEW library
GLFW library
Rendering pipeline
Shaders
Standard chrono library
GLSL scripting
VAO VBO
Shader program

## What issues I faced and how did I overcome them
I could not render a color - Once I learned how does an OpenGL buffer works, I knew I had to set my GLFW context in order to let it render anything at all.
I could not pass std:string to fprintf function - I switched to <iostream> library and use std::cout now
I had errors when tried to do premade structs in my Errors namespace - I made all premade structs static, so they're only created once
Couldn't initialize GLEW - had to turn on glewExperimental mode so I can use modern OpenGL, had to set GLFW context before I initialize GLEW, had to check if glewInit() is equal to GLEW_OK instead of true
Couldn't compile shaders - Had an error in glGetShaderiv which was returning shader parameter as false (GL_COMPILE_STATUS) instead of true