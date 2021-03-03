#include "nyx_pch.hpp"
#include "IndexBuffer.hpp"

namespace Nyx {

    std::shared_ptr<IndexBuffer> IndexBuffer::create() {
        GLuint id;
        glGenBuffers(1, &id);
        return std::shared_ptr<IndexBuffer>(new IndexBuffer(id));
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::create(GLsizei vertexCount, const std::uint32_t* data, GLenum usage) {
        auto buffer = create();
        buffer->bind();
        buffer->setData(vertexCount, data, usage);
        return std::move(buffer);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) : 
        m_id(other.m_id) 
    {
        other.m_id = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) {
        destroy();
        m_id = other.m_id;
        other.m_id = 0;

        return *this;
    }

    IndexBuffer::~IndexBuffer() {
        destroy();
    }

    void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBuffer::setData(GLsizei vertexCount, const std::uint32_t* data, GLenum usage) {
        bind();
        m_vertexCount = vertexCount;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(std::uint32_t), data, usage);
    }

    void IndexBuffer::setSubData(GLintptr offset, GLsizeiptr count, const void* data) {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(std::uint32_t), count * sizeof(std::uint32_t), data);
    }

    GLsizei IndexBuffer::getVertexCount() const {
        return m_vertexCount;
    }

    IndexBuffer::IndexBuffer(GLuint id) : m_id(id) {}

    void IndexBuffer::destroy() {
        if (m_id)
            glDeleteBuffers(1, &m_id);
    }
}