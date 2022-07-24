#include "Cube.hpp"

Cube::Cube()
{
	vertexCount = 8;
	elementCount = 12;

	static unsigned int elements_[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 5,
		0, 4, 5,
		0, 3, 7,
		0, 4, 7,
		1, 2, 6,
		1, 5, 6,
		2, 3, 7,
		2, 6, 7,
		4, 5, 6,
		4, 6, 7
	};

	elements = elements_;

	static float vertices_[] = {
	-1.f, -1.f, -1.f,
	-1.f, 1.f, -1.f,
	1.f, 1.f, -1.f,
	1.f, -1.f, -1.f,
	-1.f, -1.f, 1.f,
	-1.f, 1.f, 1.f,
	1.f, 1.f, 1.f,
	1.f, -1.f, 1.f
	};

	vertices = vertices_;
}