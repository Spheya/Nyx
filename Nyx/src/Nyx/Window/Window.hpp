#pragma once

#include "Nyx/Maths.hpp"
#include "GlfwIncludes.hpp"
#include "Input.hpp"

namespace Nyx {
	class Window {
	public:
		enum class Mode {
			WINDOWED,
			BORDERLESS,
			FULLSCREEN
		};

		Window(const char* title, Mode windowMode = Mode::WINDOWED, GLFWmonitor* monitor = nullptr);
		Window(const char* title, int width, int height, GLFWmonitor* monitor = nullptr);
		~Window() = default;

		Window(Window&&) = default;
		Window& operator=(Window&&) = default;

		Window(Window&) = delete;
		Window& operator=(Window&) = delete;

		void destroy();
		[[nodiscard]] bool isCloseRequested() const;
		void update();
		static void clear(bool colour, bool depth, bool stencil);

		void makeCurrentContext();

		void enableVsync(bool enable = true);
		void disableVsync();

		void setTitle(const char* title);

		[[nodiscard]] int getWindowWidth() const;
		[[nodiscard]] int getWindowHeight() const;
		[[nodiscard]] glm::vec2 getWindowSize() const;

		[[nodiscard]] float getDeltaTime() const;
		[[nodiscard]] float getTime() const;

		void setMode(Mode windowMode, int width, int height, GLFWmonitor* monitor = nullptr);

		[[nodiscard]] const Input* getInput() const;
		[[nodiscard]] const std::shared_ptr<Input>& getInput();

	private:
		void setWindow(GLFWwindow* window);

		static GLFWwindow* createBorderlessWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate);
		static GLFWwindow* createWindowedWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate);
		static GLFWwindow* createFullscreenWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate, GLFWmonitor* monitor);

		float m_deltaTime = 0.0f;
		float m_time = 0.0f;

		GLFWwindow* m_window = nullptr;

		struct Data {
			int width = 0, height = 0;
			const char* title;
			Data(int width, int height, const char* title) : width(width), height(height), title(title) {}
		};

		std::unique_ptr<Data> m_data;

		std::shared_ptr<Input> m_input;
	};
}
