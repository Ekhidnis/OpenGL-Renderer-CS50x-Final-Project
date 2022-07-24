#include "Mesh.hpp"

Mesh::Mesh(int flag)
{
	Primitive* primitive = CreateMesh(flag);

	if (!primitive)
	{
		std::cout << "Couldn't create mesh.\n";
	}
	else
	{
		AddMeshToBuffer(
			primitive->GetVertices(),
			primitive->GetElements(),
			primitive->vertexCount,
			primitive->elementCount
		);

		RenderMesh();
	};
}

Primitive* Mesh::CreateMesh(int flag)
{
	Primitive* UpcastedPrimitive{ nullptr };
	
	if (flag == MESH_TRIANGLE)
	{
		Triangle mesh;
		UpcastedPrimitive = &mesh;
	}
	else if (flag == MESH_PLANE)
	{
		Plane mesh;
		UpcastedPrimitive = &mesh;
	}
	else if (flag == MESH_PYRAMID)
	{
		Pyramid mesh;
		UpcastedPrimitive = &mesh;
	}
	else if (flag == MESH_CUBE)
	{
		Cube mesh;
		UpcastedPrimitive = &mesh;
	}
	else 
	{
		std::cout << "Invalid flag.\n";
	}

	return UpcastedPrimitive;
}

void Mesh::AddMeshToBuffer(float* vertices, unsigned int* elements, unsigned int vertexCount, unsigned int elementCount)
{
	elementsCount = elementCount;

	glGenBuffers(1, &elementsBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(elements[0]), elements, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

			glGenBuffers(1, &vertexBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	UnbindObjects();
}

void Mesh::RenderMesh()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferObject);
	
		glBindVertexArray(vertexArrayObject);
	
			glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);

	UnbindObjects();
}

void Mesh::UnbindObjects()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}