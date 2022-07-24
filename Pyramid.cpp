#include "Pyramid.hpp"

Pyramid::Pyramid()
{
	vertexCount = 4;
	elementCount = 4;

	static unsigned int elements_[] = {
	0, 3, 1,
	3, 2, 1,
	2, 1, 0,
	3, 2, 0
	};

	elements = elements_;

	static float vertices_[] = {
	-1.f, -1.f, 0.f,
	0.f, 0.f, 1.f,
	1.f, -1.0f, 0.f,
	0.f, 1.f, 0.f
	};

	vertices = vertices_;
}