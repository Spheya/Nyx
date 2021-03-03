#pragma once

#include <memory>

#include "Graphics.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace Nyx {
	class VertexArray {
	public:
		static std::shared_ptr<VertexArray> create();

		VertexArray(VertexArray&) = delete;
		VertexArray& operator=(VertexArray&) = delete;

		VertexArray(VertexArray&& other);
		VertexArray& operator=(VertexArray&& other);

		~VertexArray();

		void bind();

		void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
		void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

		void draw();

	private:
		explicit VertexArray(GLuint id);

		void destroy();

		GLuint m_id = 0;
		GLuint m_attribId = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_vbos;
		std::shared_ptr<IndexBuffer> m_ibo = nullptr;
	};
}

