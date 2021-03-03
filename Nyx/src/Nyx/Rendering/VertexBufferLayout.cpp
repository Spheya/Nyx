#include "nyx_pch.hpp"
#include "VertexBufferLayout.hpp"

namespace Nyx {
	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<Element>& elements) :
		m_elements(elements) {
		GLsizei offset = 0;
		for (auto& element : m_elements) {
			element.offset = offset;
			offset += element.size;
		}

		m_stride = offset;
	}

	const std::vector<VertexBufferLayout::Element>& VertexBufferLayout::getElements() const {
		return m_elements;
	}

	GLsizei VertexBufferLayout::getStride() const {
		return m_stride;
	}

}