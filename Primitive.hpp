#pragma once

class Primitive
{
public:
	const unsigned int POINTS = 3;
	unsigned int vertexCount{ 0 };
	unsigned int elementCount{ 0 };
	unsigned int* elements{ nullptr };
	float* vertices{ nullptr };

	unsigned int* GetElements() { return elements; };
	float* GetVertices() { return vertices; };
};

// child classes
#include "Triangle.hpp"
#include "Plane.hpp"
#include "Pyramid.hpp"
#include "Cube.hpp"

