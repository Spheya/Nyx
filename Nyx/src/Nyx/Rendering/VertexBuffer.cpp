#include "nyx_pch.hpp"
#include "VertexBuffer.hpp"

namespace Nyx {

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexBufferLayout& layout) {
        GLuint id;
        glGenBuffers(1, &id);
        return std::shared_ptr<VertexBuffer>(new VertexBuffer(layout, id));
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexBufferLayout& layout, GLsizei size, const void* data, GLenum usage) {
        auto buffer = create(layout);
        buffer->bind();
        buffer->setData(size, data, usage);
        return std::move(buffer);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) : 
        m_id(other.m_id),
        m_layout(std::move(other.m_layout))
    {
        other.m_id = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) {
        destroy();
        
        m_id = other.m_id;
        m_layout = std::move(other.m_layout);

        other.m_id = 0;

        return *this;
    }

    VertexBuffer::~VertexBuffer() {
        destroy();
    }

    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::setData(GLsizei size, const void* data, GLenum usage) {
        bind();
        m_bufferSize = size;
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    void VertexBuffer::setSubData(GLintptr offset, GLsizeiptr size, const void* data) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    GLsizei VertexBuffer::getSize() const {
        return m_bufferSize;
    }

    const VertexBufferLayout& VertexBuffer::getLayout() const {
        return m_layout;
    }

    VertexBuffer::VertexBuffer(const VertexBufferLayout& layout, GLuint id) : m_id(id), m_layout(layout) {}

    void VertexBuffer::destroy() {
        if (m_id)
            glDeleteBuffers(1, &m_id);
    }
}