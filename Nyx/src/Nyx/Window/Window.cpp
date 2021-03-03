#include "nyx_pch.hpp"
#include "Nyx/Core/Base.hpp"
#include "Window.hpp"

namespace Nyx {
	Window::Window(const char* title, Mode windowMode, GLFWmonitor* monitor) :
		m_data(std::make_unique<Data>(0, 0, title)),
		m_input(std::make_shared<Input>(nullptr)) {
		setMode(windowMode, 640, 480, monitor);
		NYX_CORE_INFO("Window initialized");
	}

	Window::Window(const char* title, int width, int height, GLFWmonitor* monitor) :
		m_data(std::make_unique<Data>(width, height, title)),
		m_input(std::make_shared<Input>(nullptr)) {
		setMode(Mode::WINDOWED, width, height, monitor);
		NYX_CORE_INFO("Window initialized");
	}

	void Window::destroy() {
		glfwDestroyWindow(m_window);
		NYX_CORE_INFO("Window destroyed");
	}

	bool Window::isCloseRequested() const {
		return glfwWindowShouldClose(m_window);
	}

	void Window::update() {
		glfwSwapBuffers(m_window);
		glfwPollEvents();

		// Calculate the deltatime
		const float time = float(glfwGetTime());
		m_deltaTime = time - m_time;
		m_time = time;

		// Prepare input for the next frame
		m_input->update(m_deltaTime);

		// Display the fps
		std::ostringstream ss;
		ss.precision(2);
		ss << m_data->title << " - FPS: " << (int) (1.0f / m_deltaTime) << " (" << m_deltaTime * 1000.0f << "ms" << ")";
		glfwSetWindowTitle(m_window, ss.str().c_str());
	}

	void Window::clear(bool colour, bool depth, bool stencil) {
		glClear((colour ? GL_COLOR_BUFFER_BIT : 0x0) | (depth ? GL_DEPTH_BUFFER_BIT : 0x0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0x0));
	}

	void Window::makeCurrentContext() {
		glfwMakeContextCurrent(m_window);
		NYX_CORE_INFO("OpenGL context bound");
	}

	void Window::enableVsync(bool enable) {
		glfwSwapInterval(enable ? 1 : 0);
	}

	void Window::disableVsync() {
		enableVsync(false);
	}

	void Window::setTitle(const char* title) {
		m_data->title = title;
		glfwSetWindowTitle(m_window, title);
	}

	int Window::getWindowWidth() const {
		return m_data->width;
	}

	int Window::getWindowHeight() const {
		return m_data->height;
	}

	glm::vec2 Window::getWindowSize() const {
		return glm::vec2(m_data->width, m_data->height);
	}

	float Window::getDeltaTime() const {
		return m_deltaTime;
	}

	float Window::getTime() const {
		return m_time;
	}

	void Window::setMode(Mode windowMode, int width, int height, GLFWmonitor* monitor) {
		if (monitor == nullptr)
			monitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		if (windowMode == Mode::WINDOWED) {
			m_data->width = width;
			m_data->height = height;
		} else {
			m_data->width = mode->width;
			m_data->height = mode->height;
		}

		if (m_window)
			glfwDestroyWindow(m_window);

		switch (windowMode) {
			case Mode::WINDOWED:
				setWindow(createWindowedWindow(m_data->title, m_data->width, m_data->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate));
				NYX_CORE_INFO("WindowMode set to: Windowed");
				break;
			case Mode::BORDERLESS:
				setWindow(createBorderlessWindow(m_data->title, m_data->width, m_data->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate));
				NYX_CORE_INFO("WindowMode set to: Borderless");
				break;
			case Mode::FULLSCREEN:
				setWindow(createFullscreenWindow(m_data->title, m_data->width, m_data->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate, monitor));
				NYX_CORE_INFO("WindowMode set to: Fullscreen");
				break;
			default:
				NYX_CORE_DEBUGBREAK("Invalid windowmode provided");
				break;
		}

		// Center the window
		int originX, originY;
		glfwGetMonitorPos(monitor, &originX, &originY);
		glfwSetWindowPos(m_window, originX + (mode->width - m_data->width) / 2, originY + (mode->height - m_data->height) / 2);
	}

	const Input* Window::getInput() const {
		return m_input.get();
	}

	const std::shared_ptr<Input>& Window::getInput() {
		return m_input;
	}
	
	void Window::setWindow(GLFWwindow* window) {
		m_window = window;
		m_input->setParent(window);

		glfwSetWindowUserPointer(m_window, m_data.get());
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			auto data = (Data*)glfwGetWindowUserPointer(window);
			data->width = width;
			data->height = height;
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow*) {
			NYX_CORE_INFO("Window close requested");
		});

		if (!m_window) {
			NYX_CORE_DEBUGBREAK("Something really went wrong when setting up the window");
			glfwTerminate();
			std::terminate();
		}
	}

	GLFWwindow* Window::createBorderlessWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate) {
		glfwWindowHint(GLFW_RED_BITS, redBits);
		glfwWindowHint(GLFW_GREEN_BITS, greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);

		return glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	GLFWwindow* Window::createWindowedWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate) {
		glfwWindowHint(GLFW_RED_BITS, redBits);
		glfwWindowHint(GLFW_GREEN_BITS, greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);

		return glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	GLFWwindow* Window::createFullscreenWindow(const char* title, int width, int height, int redBits, int greenBits, int blueBits, int refreshRate, GLFWmonitor* monitor) {
		glfwWindowHint(GLFW_RED_BITS, redBits);
		glfwWindowHint(GLFW_GREEN_BITS, greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

		return glfwCreateWindow(width, height, title, monitor, nullptr);
	}
}