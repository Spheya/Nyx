#include "nyx_pch.hpp"
#include "VertexArray.hpp"

namespace Nyx {

	std::shared_ptr<VertexArray> VertexArray::create() {
		GLuint id;
		glGenVertexArrays(1, &id);
		return std::shared_ptr<VertexArray>(new VertexArray(id));
	}

	VertexArray::VertexArray(GLuint id) : m_id(id) {}

	VertexArray::VertexArray(VertexArray&& other) : 
		m_id(other.m_id) 
	{
		other.m_id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) {
		destroy();
		m_id = other.m_id;
		other.m_id = 0;

		return *this;
	}

	VertexArray::~VertexArray() {
		destroy();
	}

	void VertexArray::bind() {
		glBindVertexArray(m_id);
	}

	void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
		bind();
		vertexBuffer->bind();

		NYX_CORE_WARN_ASSERT(vertexBuffer->getLayout().getElements().size() > 0, "An empty VertexBuffer has been added to a VertexArray");

		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout.getElements()) {
			if (element.type == ShaderDataType::MAT3 || element.type == ShaderDataType::MAT4) {
				// Matrix
				glEnableVertexAttribArray(m_attribId);
				for (GLuint i = 0; i < element.componentCount; i++) {
					glVertexAttribPointer(
						m_attribId,
						element.componentCount,
						element.openGlType,
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.getStride(),
						(const void*) (element.offset + GLsizei(i * element.componentCount) * sizeof(float))
					);
					++m_attribId;
				}

			} else {
				// Non-Matrix
				glEnableVertexAttribArray(m_attribId);
				glVertexAttribPointer(
					m_attribId,
					element.componentCount,
					element.openGlType,
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.getStride(),
					(const void*) (size_t) element.offset
				);
				++m_attribId;
			}
		}

		m_vbos.push_back(std::move(vertexBuffer));
	}

	void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
		bind();
		indexBuffer->bind();
		m_ibo = std::move(indexBuffer);
	}

	void VertexArray::draw() {
		bind();

		NYX_CORE_ASSERT(!m_vbos.empty(), "Trying to render an empty VertexArray");

		if (m_ibo) {
			glDrawElements(GL_TRIANGLES, m_ibo->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		} else {
			const auto& firstBuffer = *m_vbos[0];
			glDrawArrays(GL_TRIANGLES, 0, firstBuffer.getSize() / firstBuffer.getLayout().getStride());
		}
	}

	void VertexArray::destroy() {
		if (m_id)
			glDeleteVertexArrays(1, &m_id);
	}
}
