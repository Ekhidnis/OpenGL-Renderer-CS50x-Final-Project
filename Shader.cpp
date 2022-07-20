#include "Shader.hpp"

Shader::Shader(const char* shaderPath)
{
	shader = ReadShaderFile(shaderPath);
}

std::string Shader::ReadShaderFile(const char* shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);

		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();
		shaderCode = shaderStream.str();

		shaderFile.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader code located at '" << shaderPath << "' cannot be read." << std::endl;
	}

	return shaderCode;
}