#pragma once

namespace Nyx {
	enum class ShaderDataType {
		FLOAT, VEC2, VEC3, VEC4,
		MAT3, MAT4,
		INT, IVEC2, IVEC3, IVEC4,
		BOOL,
	};

	static GLint getShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::FLOAT:		return 4 * 1;
			case ShaderDataType::VEC2:		return 4 * 2;
			case ShaderDataType::VEC3:		return 4 * 3;
			case ShaderDataType::VEC4:		return 4 * 4;

			case ShaderDataType::MAT3:		return 4 * 3 * 3;
			case ShaderDataType::MAT4:		return 4 * 4 * 4;

			case ShaderDataType::INT:		return 4 * 1;
			case ShaderDataType::IVEC2:		return 4 * 2;
			case ShaderDataType::IVEC3:		return 4 * 3;
			case ShaderDataType::IVEC4:		return 4 * 4;

			case ShaderDataType::BOOL:		return 1;
		}

		NYX_CORE_DEBUGBREAK("An invalid ShaderDataType has been provided!"); return 0;
	}

	static GLuint getShaderDataTypeComponentCount(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::FLOAT:		return 1;
			case ShaderDataType::VEC2:		return 2;
			case ShaderDataType::VEC3:		return 3;
			case ShaderDataType::VEC4:		return 4;

			case ShaderDataType::MAT3:		return 3;
			case ShaderDataType::MAT4:		return 4;

			case ShaderDataType::INT:		return 1;
			case ShaderDataType::IVEC2:		return 2;
			case ShaderDataType::IVEC3:		return 3;
			case ShaderDataType::IVEC4:		return 4;

			case ShaderDataType::BOOL:		return 1;
		}

		NYX_CORE_DEBUGBREAK("An invalid ShaderDataType has been provided!"); return 0;
	}

	static GLenum getShaderDataTypeOpenGlType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::FLOAT:		return GL_FLOAT;
			case ShaderDataType::VEC2:		return GL_FLOAT;
			case ShaderDataType::VEC3:		return GL_FLOAT;
			case ShaderDataType::VEC4:		return GL_FLOAT;

			case ShaderDataType::MAT3:		return GL_FLOAT;
			case ShaderDataType::MAT4:		return GL_FLOAT;

			case ShaderDataType::INT:		return GL_INT;
			case ShaderDataType::IVEC2:		return GL_INT;
			case ShaderDataType::IVEC3:		return GL_INT;
			case ShaderDataType::IVEC4:		return GL_INT;

			case ShaderDataType::BOOL:		return GL_BOOL;
		}

		NYX_CORE_DEBUGBREAK("An invalid ShaderDataType has been provided!"); return 0;
	}
}