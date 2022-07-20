#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Errors.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	Renderer(GLFWwindow* Window);

	const char* PATH_SHADER_VERTEX = "vertex.shader";
	const char* PATH_SHADER_FRAGMENT = "fragment.shader";

	Shader* vertexShader{ nullptr }; // mozhet sdelat array?
	Shader* fragmentShader{ nullptr };

	const char* TITLE = "Renderer";
	struct Errors::Status Status = Errors::RendererNotInit;
	GLFWwindow* Window{ nullptr };
	int windowWidth{ 0 };
	int windowHeight{ 0 };
	float windowAspectRatio{ 0 };

	// shader
	unsigned int vao{ 0 }; // vertex array object
	unsigned int vbo{ 0 }; // vertex buffer object
	unsigned int ebo{ 0 }; // elements buffer object
	unsigned int shaderProgram{ 0 };
	
	// uniforms
	unsigned int uniformModelMatrix{ 0 }; // local space
	unsigned int uniformProjectionMatrix{ 0 }; // view space

	// projection
	const float FIELD_OF_VIEW = 90.f;
	const float FRUSTRUM_PLANE_NEAR = 0.001f;
	const float FRUSTRUM_PLANE_FAR = 10000.f;

	// translation
	const float STEP_LOC = 0.005f; // Fixed amount of units to translate
	const float OFFSET_TRANSLATION_LIMIT_X = 4.f;
	const float OFFSET_TRANSLATION_LIMIT_Y = 4.f;
	const float OFFSET_TRANSLATION_LIMIT_Z = 4.f;

	float offsetTranslationX{ 0.f };
	float offsetTranslationY{ 0.f };
	float offsetTranslationZ = -1.5f;
	bool translationDirectionX{ false };
	bool translationDirectionY{ false };
	bool translationDirectionZ{ false };
	
	// rotation
	const float STEP_ROT = 1.f; // Fixed amount of angles to translate
	const float TO_RADIANS = 3.14159265f / 180.f;
	const float OFFSET_ROTATION_LIMIT = 360.f;

	float offsetRotationAngleX{ 0.f };
	float offsetRotationAngleY{ 0.f };
	float offsetRotationAngleZ{ 0.f };

	// scale
	const float StepScale = 0.05f; // Fixed amount of units to scale
	float offsetScaleX = 0.2f;
	float offsetScaleY = 0.2f;
	float offsetScaleZ = 0.2f;
	bool scaleDirectionX{ false };
	bool scaleDirectionY{ false };
	bool scaleDirectionZ{ false };


	// initialization
	int Initialize();
	void AdjustViewport();
	void Success();
	bool Ready();

	// getters
	int GetStatusID();
	std::string GetStatusText();

	// uniforms
	void GetUniformLocations(int ShaderProgram);
	void UpdateUniforms();
	void AssignUniforms();

	// rendering
	void EnableFeatures();
	void MakeShaders();
	void AddShader(int ShaderProgram, const char* ShaderCode, GLenum ShaderType);
	void CompileShaderProgram();
	void CreatePyramid();
	void DrawBuffer();
	void UseProgram();

	// validation
	bool CheckShader(unsigned int Shader, GLenum ShaderType);
	bool LinkProgram(unsigned int shaderProgram);
	bool ValidateProgram(unsigned int shaderProgram);
};