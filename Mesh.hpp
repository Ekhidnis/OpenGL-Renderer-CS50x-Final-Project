#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Primitive.hpp"

// Mesh flags
#define MESH_TRIANGLE 1
#define MESH_PLANE 2
#define MESH_PYRAMID 3
#define MESH_CUBE 4

class Mesh
{
public:
	unsigned int vertexArrayObject{ 0 };
	unsigned int vertexBufferObject{ 0 };
	unsigned int elementsBufferObject{ 0 };
	unsigned int elementsCount{ 0 };

	/*
	MESH_TRIANGLE
	MESH_PLANE
	MESH_PYRAMID
	MESH_CUBE
	*/
	Mesh(int flag);

	Primitive* CreateMesh(int flag);
	void AddMeshToBuffer(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfElements);
	void RenderMesh();
	void UnbindObjects();
};

