#pragma once

#include "Graphics.hpp"

namespace Nyx {
	class Texture2D {
	public:
		static std::shared_ptr<Texture2D> create(GLsizei width, GLsizei height);
		static std::shared_ptr<Texture2D> create(const std::string& file);
	
		Texture2D(Texture2D&) = delete;
		Texture2D& operator=(Texture2D&) = delete;

		Texture2D(Texture2D&& other);
		Texture2D& operator=(Texture2D&& other);

		~Texture2D();

		void store(void* data);
		void store(void* data, GLint x, GLint y, GLsizei w, GLsizei h);

		void bind(GLuint slot) const;

		GLsizei getWidth() const;
		GLsizei getHeight() const;

	private:
		Texture2D(GLuint id, GLsizei width, GLsizei height);

		GLuint m_id;
		GLsizei m_width, m_height;
	};
}