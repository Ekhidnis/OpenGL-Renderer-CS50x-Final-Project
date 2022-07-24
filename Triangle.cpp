#include "Triangle.hpp"

Triangle::Triangle()
{
	vertexCount = 3;
	elementCount = 1;

	static unsigned int elements_[] = {
	0, 1, 2
	};

	elements = elements_;

	static float vertices_[] = {
		-1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		1.f, -1.f, 0.f
	};

	vertices = vertices_;
}