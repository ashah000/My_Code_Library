#include "Mesh.h"



Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;
	// Graphics card is creating vertex Array.
	glGenVertexArrays(1, &VAO); //A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object.
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	//Vertex Buffer Object,  VBOs can also store information such as normals, texcoords, indicies, etc.
	glGenBuffers(1, &VBO); // A Vertex Buffer Object(VBO) is a memory buffer in the high speed memory of your video card designed to hold information about vertices.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //define an array of generic vertex attribute data
	glEnableVertexAttribArray(0); // location = 0

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbinding it only after unbinding VAO.
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO); // Bind Vertex Array Object for rendering to GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO); // Delete Graphics Memory Buffers.
		IBO = 0;
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO); // Delete Graphics Memory Buffers.
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO); // Delete Graphics Memory Buffers.
		VAO = 0;
	}
	indexCount = 0;
}

Mesh::~Mesh()
{
	ClearMesh();
}
