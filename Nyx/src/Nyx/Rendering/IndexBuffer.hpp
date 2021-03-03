#pragma once

#include <memory>

#include "Graphics.hpp"

namespace Nyx {

	class IndexBuffer {

	public:
		static std::shared_ptr<IndexBuffer> create();
		static std::shared_ptr<IndexBuffer> create(GLsizei vertexCount, const std::uint32_t* data, GLenum usage = GL_STATIC_DRAW);

		IndexBuffer(IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& other);
		IndexBuffer& operator=(IndexBuffer&& other);

		~IndexBuffer();

		void bind();
		void setData(GLsizei vertexCount, const std::uint32_t* data, GLenum usage = GL_STATIC_DRAW);
		void setSubData(GLintptr offset, GLsizeiptr count, const void* data);

		GLsizei getVertexCount() const;

	private:
		explicit IndexBuffer(GLuint id);

		void destroy();

		GLuint m_id = 0;
		GLsizei m_vertexCount = 0;
	};
}