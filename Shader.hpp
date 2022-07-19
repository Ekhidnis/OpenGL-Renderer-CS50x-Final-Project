#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	std::string ReadShaderFile(const char* shaderPath);
	void CreateFromFiles(const char* vShader, const char* fShader);
};
