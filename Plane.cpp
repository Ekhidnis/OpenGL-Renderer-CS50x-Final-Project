#include "Plane.hpp"

Plane::Plane()
{
	vertexCount = 4;
	elementCount = 2;

	static unsigned int elements_[] = {
		0, 1, 2,
		2, 3, 0
	};

	elements = elements_;

	static float vertices_[] = {
		-1.f, -1.f, 0.f,
		-1.f, 1.f, 0.f,
		1.f, 1.f, 0.f,
		1.f, -1.f, 0.f
	};

	vertices = vertices_;
}