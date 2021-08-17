#pragma once
#include <src/Renderer/Shader.h>
#include <array>
#include "Renderer.h"
const unsigned int MAX_QUAD_COUNT = 1024;
const unsigned int MAX_VERTEX_COUNT = MAX_QUAD_COUNT * 4;
const unsigned int MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;
struct Vec3
{
	float array[3];
};
struct Vec4
{
	float array[4];
};
struct Vertex
{
	Vec3 Position;
	Vec4 Color;
};



class OpenGLRenderer
{
public:
	OpenGLRenderer()
	{

	}
	unsigned int QuadCount()
	{
		return vertex_count / 4;
	}
	unsigned int VertexCount()
	{
		return vertex_count;
	}
	void Init()
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < MAX_INDEX_COUNT; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		batch_shader = Shader("Shaders/Batch.vert", "Shaders/Batch.frag");

		//Generate buffers

		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Allocate buffers
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_COUNT * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

		//Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);

		//Color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glEnableVertexAttribArray(1);

		//Unbind stuff
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void BeginFrame()
	{
		vertex_count = 0;
		index_count = 0;

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		batch_shader.use();
	}
	void EndFrame()
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());


		//Bind vao
		glBindVertexArray(VAO);
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	}
	void DrawQuad(f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a)
	{
		//Bottom right
		Vertex v0;
		v0.Position = { x + w, y - h, 1.f };
		v0.Color = { r,g,b,a };
		vertices[vertex_count] = v0;
		vertex_count++;

		//Top right
		Vertex v1;
		v1.Position = { x + w, y, 1.f };
		v1.Color = { r, g, b, a };
		vertices[vertex_count] = v1;
		vertex_count++;

		//Top left
		Vertex v2;
		v2.Position = { x, y, 1.f };
		v2.Color = { r, g, b, a };
		vertices[vertex_count] = v2;
		vertex_count++;

		//Bottom left
		Vertex v3;
		v3.Position = { x, y - h, 1.f };
		v3.Color = { r, g, b, a };
		vertices[vertex_count] = v3;
		vertex_count++;

		index_count += 6;
	}
	Shader& GetShader()
	{
		return batch_shader;
	}
private:
	std::array<Vertex, MAX_VERTEX_COUNT> vertices;
	std::array<unsigned int, MAX_INDEX_COUNT> indices;
	unsigned int vertex_count = 0;
	unsigned int index_count = 0;
	Shader batch_shader;
	unsigned int VAO, VBO, EBO;
};