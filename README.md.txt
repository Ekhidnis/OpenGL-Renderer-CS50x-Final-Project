# Ekhidnis' OpenGL Renderer (CS50x Final Project)
#### Video Demo:  <URL HERE>
#### Description: Small-scale renderer made using OpenGL libraries on top of C++ language.


## Reasoning
I understand and feel guilty that my project is not trying to bring anything useful to the world, but I can't withstand the urge to invest my time into learning engines and graphics, because it lights the fire in my eyes.


## The Goal
For the final project I want to have something 3D moving on a screen (most importantly I want to understand how the graphics are working), but after that I will proceed developing this engine. 
I'm also interested in planning and architecture, so I set a secondary objective for which I will have to invest some time into these topics and have somewhat of an adequate code structure.


## Technical stack
OpenGL - Open Graphics Library;

GLEW - OpenGL Extension Wrangler which is an extensions manager and an interface for OpenGL.
	To use GLEW we should include header (#include <GL/glew.h>);
	To access the latest features of OpenGL we should set variable experimental mode to true (glewExperimental = GL_TRUE);
	Then we need to initialize the interface and check if the initialization was successful;

GLFW - I couldn't find what the abbreviature stands for. GLFW OpenGL library that is specifically made for managing windows and input. (I choose this as a lightweight and simple alternative to SDL since I'm planning a small-scale project with no audio and other features SDL provides)
	To use GLFW we should include header (#include <GLFW/glfw3.h>)
	Then we need to initialize it and check if the initialization was successful;

GLM - OpenGL Mathematics library. Mostly used for vector and matrix operations.


## Files
Main.cpp - Defines the program itself. That's where program start and end.
Structure.txt - Reflects current program structure
Components/Window.* - Class responsible for creation of a window for program
Components/Renderer.* - Class responsible for drawing on the given window
Shaders/Shader.* - Class responsible for creation shaders (is read from the files)
Shaders/*.shader - Raw data file responsible for storing GLSL shader code
Utility/Errors.hpp - Namespace with struct responsible for structurization of error IDs and names
Utility/Statistics.* - Class responsible for collecting useful info like runtime duration, renderered frames, frames per second 


## What it can do at the moment
Create and initialize window (initializes opengl stack and operates created window)
Create and initialize statistics (has timer and fps counter)
Has Errors namespace where types of errors are declared and used throughout the code
Draws object
Moves object
Rotates object
Has projection(view space) and model(local space) matrixes


## TODO
Add camera movement
Add mesh class
Add object class
Add textures
Add ability to spawn or move or delete objects runtime
And many more...


## What aspects I had to invest my time in and gain knowledge about
Implementing libraries
GLEW library
GLFW library
GLM library
Rendering pipeline
Shaders
Standard chrono library
GLSL scripting
VAO VBO
Shader program
Matrixes


## What issues I faced and how did I overcome them
I could not render a color - Once I learned how does an OpenGL buffer works, I knew I had to set my GLFW context in order to let it render anything at all.
I could not pass std:string to fprintf function - I switched to <iostream> library and use std::cout now
I had errors when I tried to do premade structs in my Errors namespace - I made all premade structs static, so they're only created once
Couldn't initialize GLEW - had to turn on glewExperimental mode so I can use modern OpenGL, had to set GLFW context before I initialize GLEW, had to check if glewInit() is equal to GLEW_OK instead of true
Couldn't compile shaders - Had an error in glGetShaderiv which was returning shader parameter as false (GL_COMPILE_STATUS) instead of true
Can't get uniform matrices in shaders to work with the renderer - My matrix was not initialized so I had to set it to identity matrix using prebuilt construct
Couldn't get window to scale when I resize it - Had to pass references instead of pointers, because the function glfwGetFramebufferSize has inbuilt option to not return a value if it's a null