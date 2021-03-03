#pragma once

#include <memory>

#include "Window/Window.hpp"
#include "Window/GlfwGuard.hpp"

#include "Core/Logger.hpp"

namespace Nyx {

	class RenderContext
	{
	public:
		RenderContext(const char* title, Window::Mode windowMode = Window::Mode::WINDOWED) :
			m_window(title, windowMode)
		{
			init();
		}
		
		RenderContext(const char* title, int width, int height) :
			m_window(title, width, height)
		{
			init();
		}

		Window& getWindow() { return m_window; }
		const Window& getWindow() const { return m_window; }

	private:

		void init() {
			m_window.makeCurrentContext();
			m_window.disableVsync();

			if (glewInit() == GLEW_OK) {
				NYX_CORE_INFO("GLEW setup completed");
			} else {
				NYX_CORE_ERROR("GLEW setup failed");
			}

#ifdef NYX_ENABLE_LOGGER
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(openGlMessageCallback, 0);
#endif
		}

		GlfwGuard m_glfwGuard;
		Window m_window;

#ifdef NYX_ENABLE_LOGGER
		static void openGlMessageCallback(GLenum source, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
		{
			std::string sourceString;
			std::string typeString;
			
			switch (source) {
				case GL_DEBUG_SOURCE_API: sourceString = "API"; break;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceString = "WINDOW_SYSTEM"; break;
				case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "SHADER_COMPILER"; break;
				case GL_DEBUG_SOURCE_THIRD_PARTY: sourceString = "THIRD_PARTY"; break;
				case GL_DEBUG_SOURCE_APPLICATION: sourceString = "APPLICATION"; break;
				case GL_DEBUG_SOURCE_OTHER: sourceString = "OTHER"; break;
				default: sourceString = std::to_string(source);
			}

			switch (type) {
				case GL_DEBUG_TYPE_ERROR: typeString = "ERROR";
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "DEPRECATED_BEHAVIOR";
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeString = "UNDEFINED_BEHAVIOR";
				case GL_DEBUG_TYPE_PORTABILITY: typeString = "PORTABILITY";
				case GL_DEBUG_TYPE_PERFORMANCE: typeString = "PERFORMANCE";
				case GL_DEBUG_TYPE_MARKER: typeString = "MARKER";
				case GL_DEBUG_TYPE_PUSH_GROUP: typeString = "PUSH_GROUP";
				case GL_DEBUG_TYPE_POP_GROUP: typeString = "POP_GROUP";
				case GL_DEBUG_TYPE_OTHER: typeString = "OTHER";
				default: typeString = std::to_string(type);
			}

			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				NYX_CORE_LOG("OpenGL: \"{0}\" (type: {1}, source: {2})", message, typeString, sourceString);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				NYX_CORE_INFO("OpenGL: \"{0}\" (type: {1}, source: {2})", message, typeString, sourceString);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				NYX_CORE_WARN("OpenGL: \"{0}\" (type: {1}, source: {2})", message, typeString, sourceString);
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				NYX_CORE_ERROR("OpenGL: \"{0}\" (type: {1}, source: {2})", message, typeString, sourceString);
				break;
			}
		}
#endif
	};
}
