#include "nyx_pch.hpp"
#include "Shader.hpp"

namespace Nyx {
    Shader::Shader(Shader&& other) : 
        m_id(other.m_id),
        m_uniformLocations(std::move(other.m_uniformLocations))
    {
        other.m_id = 0;
    }

    Shader& Shader::operator=(Shader&& other) {
        m_id = other.m_id;
        m_uniformLocations = std::move(other.m_uniformLocations);

        other.m_id = 0;

        return *this;
    }

    Shader::~Shader() {
        if (m_id)
            glDeleteProgram(m_id);
    }

    std::shared_ptr<Shader> Shader::create(const std::string& vertexSource, const std::string& fragmentSource) {
        auto vertex = createShader(vertexSource, GL_VERTEX_SHADER);
        auto fragment = createShader(fragmentSource, GL_FRAGMENT_SHADER);

        auto shader = std::shared_ptr<Shader>(new Shader(glCreateProgram()));
        NYX_CORE_ASSERT(shader->m_id != 0, "A shaderprogram was created with id 0")

        glAttachShader(shader->m_id, vertex);
        glAttachShader(shader->m_id, fragment);

        shader->linkProgram();

        glDetachShader(shader->m_id, vertex);
        glDetachShader(shader->m_id, fragment);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return shader;
    }

    std::shared_ptr<Shader> Shader::createFromFiles(const std::string& vertexFile, const std::string& fragmentFile) {
        std::ifstream vertexFileStream(vertexFile);
        std::stringstream vertexSource;
        vertexSource << vertexFileStream.rdbuf();
        
        std::ifstream fragmentFileStream(fragmentFile);
        std::stringstream fragmentSource;
        fragmentSource << fragmentFileStream.rdbuf();

        return create(vertexSource.str(), fragmentSource.str());
    }

    Shader::Shader(GLuint id) : m_id(id) {}

    void Shader::bind() const {
        glUseProgram(m_id);
    }

    void Shader::setUniform(const std::string& name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setUniform(const std::string& name, const glm::vec2& value) {
        glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::vec3& value) {
        glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::vec4& value) {
        glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::mat3& value) {
        glUniformMatrix3fv(getUniformLocation(name), 1, false, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::mat4& value) {
        glUniformMatrix4fv(getUniformLocation(name), 1, false, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setUniform(const std::string& name, const glm::ivec2& value) {
        glUniform2iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::ivec3& value) {
        glUniform3iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, const glm::ivec4& value) {
        glUniform4iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string& name, bool value) {
        glUniform1i(getUniformLocation(name), value ? 1 : 0);
    }

    void Shader::linkProgram() {
        glLinkProgram(m_id);

        GLint isLinked = 0;
        glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint logLength = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> infoLog(logLength);
            glGetProgramInfoLog(m_id, logLength, &logLength, &infoLog[0]);

            NYX_CORE_ERROR("{0}", &infoLog[0]);
            NYX_CORE_DEBUGBREAK("Shader link failure!");
            return;
        }

        glValidateProgram(m_id);

        GLint isValidated = 0;
        glGetProgramiv(m_id, GL_VALIDATE_STATUS, &isValidated);
        if (isValidated == GL_FALSE) {
            GLint logLength = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> infoLog(logLength);
            glGetProgramInfoLog(m_id, logLength, &logLength, &infoLog[0]);

            NYX_CORE_ERROR("{0}", &infoLog[0]);
            NYX_CORE_DEBUGBREAK("Shader validation failure!");
            return;
        }
    }

    GLint Shader::getUniformLocation(const std::string& name) {
        const auto& lookup = m_uniformLocations.find(name);
        if(lookup == m_uniformLocations.end()) {
            GLint location = glGetUniformLocation(m_id, name.c_str());
            m_uniformLocations[name] = location;
            return location;
        }
        return lookup->second;
    }

    GLuint Shader::createShader(const std::string& source, GLenum type) {
        GLuint shader = glCreateShader(type);

        const GLchar* rawSource = source.c_str();
        glShaderSource(shader, 1, &rawSource, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {

            GLint logLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

            glDeleteShader(shader);

            std::string shaderTypeName;
            switch (type) {
                case GL_VERTEX_SHADER:      shaderTypeName = "Vertex";      break;
                case GL_FRAGMENT_SHADER:    shaderTypeName = "Fragment";    break;
                case GL_GEOMETRY_SHADER:    shaderTypeName = "Geometry";    break;
                default:                    shaderTypeName = "INVALID";            break;
            }

            NYX_CORE_ERROR("{0}", &infoLog[0]);
            NYX_CORE_DEBUGBREAK(shaderTypeName + " shader compilation failure!");

            return 0;
        }

        return shader;
    }
}