#pragma once

#include <memory>

#include "Graphics.hpp"
#include "VertexBufferLayout.hpp"

namespace Nyx {

	class VertexBuffer {

	public:
		static std::shared_ptr<VertexBuffer> create(const VertexBufferLayout& layout);
		static std::shared_ptr<VertexBuffer> create(const VertexBufferLayout& layout, GLsizei size, const void* data, GLenum usage = GL_STATIC_DRAW);

		VertexBuffer(VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& other);
		VertexBuffer& operator=(VertexBuffer&& other);

		~VertexBuffer();

		void bind();
		void setData(GLsizei size, const void* data, GLenum usage = GL_STATIC_DRAW);
		void setSubData(GLintptr offset, GLsizeiptr size,const void* data);

		GLsizei getSize() const;

		const VertexBufferLayout& getLayout() const;

	private:
		VertexBuffer(const VertexBufferLayout & layout, GLuint id);

		void destroy();

		GLuint m_id = 0;
		VertexBufferLayout m_layout;
		GLsizei m_bufferSize;
	};
}