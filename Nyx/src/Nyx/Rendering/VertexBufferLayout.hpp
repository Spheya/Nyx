#pragma once

#include <string>

#include "Graphics.hpp"
#include "ShaderDataType.hpp"

namespace Nyx {
	class VertexBufferLayout {
	public:
		struct Element {
			ShaderDataType type;
			std::string name;
			bool normalized;
			GLint size;
			GLuint componentCount;
			GLenum openGlType;
			GLsizei offset;

			Element(ShaderDataType type, const std::string& name, bool normalized = false) :
				type(type),
				name(name),
				normalized(normalized),
				size(getShaderDataTypeSize(type)),
				componentCount(getShaderDataTypeComponentCount(type)),
				openGlType(getShaderDataTypeOpenGlType(type)),
				offset(0)
			{}
		};

		VertexBufferLayout(const std::initializer_list<Element>& elements);

		[[nodiscard]] const std::vector<Element>& getElements() const;
		[[nodiscard]] GLsizei getStride() const;

	private:
		std::vector<Element> m_elements;
		GLsizei m_stride;
	};

}