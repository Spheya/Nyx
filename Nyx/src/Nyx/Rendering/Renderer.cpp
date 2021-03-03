#include "nyx_pch.hpp"
#include "Renderer.hpp"

#include "Nyx/Maths.hpp"
#include "VertexBuffer.hpp"

Nyx::Renderer::Renderer() :
	m_raytracingShader(Shader::createFromFiles("assets/shaders/raytracing.vert", "assets/shaders/raytracing.frag")),
	m_blitMesh(VertexArray::create())
{
	struct Vertex {
		glm::vec2 position;
		glm::vec2 textureCoord;
	};

	Vertex vertices[] = {
		{ glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2( 1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec2( 1.0f,  1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(-1.0f,  1.0f), glm::vec2(0.0f, 1.0f) },
	};

	uint32_t indices[] = {
		0, 3, 2,
		0, 2, 1,
	};

	auto vbo = VertexBuffer::create(VertexBufferLayout{
		{ShaderDataType::VEC2, "a_Position"},
		{ShaderDataType::VEC2, "a_TexCoord"}},
		sizeof(vertices), vertices, GL_STATIC_DRAW);
	auto ibo = IndexBuffer::create(sizeof(indices) / sizeof(*indices), indices, GL_STATIC_DRAW);

	m_blitMesh->addVertexBuffer(vbo);
	m_blitMesh->setIndexBuffer(ibo);
}

void Nyx::Renderer::render()
{
	m_raytracingShader->bind();

	m_blitMesh->draw();
}
