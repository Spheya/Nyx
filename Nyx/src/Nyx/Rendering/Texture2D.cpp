#include "nyx_pch.hpp"
#include "Texture2D.hpp"

#include "Nyx/Core/ImageLoader.hpp"

namespace Nyx {
	Texture2D::Texture2D(GLuint id, GLsizei width, GLsizei height) :
		m_id(id),
		m_width(width),
		m_height(height)
	{}


	Texture2D::Texture2D(Texture2D&& other) :
		m_id(other.m_id),
		m_width(other.m_width),
		m_height(other.m_height)
	{
		other.m_id = 0;
	}

	Texture2D& Texture2D::operator=(Texture2D&& other) {
		m_id = other.m_id;
		m_width = other.m_width;
		m_height = other.m_height;

		other.m_id = 0;

		return *this;
	}

	Texture2D::~Texture2D() {
		if (m_id)
			glDeleteTextures(0, &m_id);
	}

	void Texture2D::store(void* data) {
		// TODO: Get datatypes as parameter
		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::store(void* data, GLint x, GLint y, GLsizei w, GLsizei h) {
		NYX_CORE_ASSERT(x >= 0 && y >= 0 && x + w < m_width && y + h < m_height, "Specified rectangle is out of bounds");

		// TODO: Get datatypes as parameter
		glTextureSubImage2D(m_id, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::bind(GLuint slot) const {
		glBindTextureUnit(slot, m_id);
	}

	GLsizei Texture2D::getWidth() const {
		return m_width;
	}

	GLsizei Texture2D::getHeight() const {
		return m_height;
	}

	std::shared_ptr<Texture2D> Texture2D::create(GLsizei width, GLsizei height) {
		GLuint id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, GLsizei(width), GLsizei(height));

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		return std::shared_ptr<Texture2D>(new Texture2D(id, width, height));
	}

	std::shared_ptr<Texture2D> Texture2D::create(const std::string& file) {
		int width, height, channels;
		stbi_uc* data = stbi_load(file.c_str(), &width, &height, &channels, 0);
		NYX_CORE_ASSERT(data, "Image file failed to load");
		NYX_CORE_ASSERT(channels == 4, "Only images in RGBA format are supported!");

		auto texture = create(GLsizei(width), GLsizei(height));
		texture->store(data);

		stbi_image_free(data);

		return texture;
	}
}