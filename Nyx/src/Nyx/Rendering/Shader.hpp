#pragma once

#include "Graphics.hpp"
#include "Nyx/Maths.hpp"

namespace Nyx {
	class Shader {
	public:
		Shader(Shader&) = delete;
		Shader& operator=(Shader&) = delete;

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);

		~Shader();

		static std::shared_ptr<Shader> create(const std::string& vertexSource, const std::string& fragmentSource);
		static std::shared_ptr<Shader> createFromFiles(const std::string& vertexFile, const std::string& fragmentFile);

		void bind() const;

		void setUniform(const std::string& name, float value);
		void setUniform(const std::string& name, const glm::vec2& value);
		void setUniform(const std::string& name, const glm::vec3& value);
		void setUniform(const std::string& name, const glm::vec4& value);

		void setUniform(const std::string& name, const glm::mat3& value);
		void setUniform(const std::string& name, const glm::mat4& value);

		void setUniform(const std::string& name, int value);
		void setUniform(const std::string& name, const glm::ivec2& value);
		void setUniform(const std::string& name, const glm::ivec3& value);
		void setUniform(const std::string& name, const glm::ivec4& value);

		void setUniform(const std::string& name, bool value);

	private:
		Shader(GLuint id);

		void linkProgram();

		GLint getUniformLocation(const std::string& name);

		static GLuint createShader(const std::string& source, GLenum type);

		GLuint m_id;
		std::unordered_map<std::string, GLint> m_uniformLocations;

	};
}
