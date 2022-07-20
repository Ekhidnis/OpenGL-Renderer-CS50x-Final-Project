#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* shaderPath);

	std::string shader;

	std::string ReadShaderFile(const char* shaderPath);
};
