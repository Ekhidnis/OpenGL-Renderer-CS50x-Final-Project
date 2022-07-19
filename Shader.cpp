#include "Shader.hpp"

std::string Shader::ReadShaderFile(const char* shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// ��������� �����
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// ��������� ������ � ������
		shaderStream << shaderFile.rdbuf();
		// ��������� �����
		shaderFile.close();
		// ��������������� ������ � ������ GLchar
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader file " << shaderPath << " cannot be read" << std::endl;
	}

	return shaderCode;
}

void Shader::CreateFromFiles(const char* vShader, const char* fShader)
{
	std::string vShaderCode = ReadShaderFile(vShader);
	std::string fShaderCode = ReadShaderFile(fShader);
}