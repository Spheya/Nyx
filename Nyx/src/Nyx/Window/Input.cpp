#include "nyx_pch.hpp"
#include "Input.hpp"

namespace Nyx {
	void keyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
		if (action == GLFW_PRESS)
			Input::buffer[window].keyboardKeys[KeyCode(key)] = true;

		if (action == GLFW_RELEASE)
			Input::buffer[window].keyboardKeys[KeyCode(key)] = false;
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/) {
		if (action == GLFW_PRESS)
			Input::buffer[window].mouseButtons[MouseButtonCode(button)] = true;

		if (action == GLFW_RELEASE)
			Input::buffer[window].mouseButtons[MouseButtonCode(button)] = false;
	}

	std::unordered_map<GLFWwindow*, Input::BufferData> Input::buffer;

	Input::Input(GLFWwindow* window) :
		m_parent(window) {
		if (window != nullptr) {
			glfwSetKeyCallback(window, keyCallback);
			glfwSetMouseButtonCallback(window, mouseButtonCallback);

			double x, y;
			glfwGetCursorPos(m_parent, &x, &y);
			m_mouseData = MouseData{ glm::vec2(float(x), float(y)), glm::vec2(0.0f) };

		}
	}

	void Input::setParent(GLFWwindow* window) {
		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		m_parent = window;

		if (m_isMouseLocked)
			enableLockedMouse();

		double x, y;
		glfwGetCursorPos(m_parent, &x, &y);
		m_mouseData = MouseData{ glm::vec2(float(x), float(y)), glm::vec2(0.0f) };
	}

	void Input::enableLockedMouse(bool enabled) {
		glfwSetInputMode(m_parent, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		m_isMouseLocked = true;

		double x, y;
		glfwGetCursorPos(m_parent, &x, &y);
		m_mouseData = MouseData{ glm::vec2(float(x), float(y)), glm::vec2(0.0f) };

	}

	void Input::disableLockedMouse() {
		enableLockedMouse(false);
	}

	bool Input::isMouseLocked() const {
		return m_isMouseLocked;
	}

	glm::vec2 Input::getMouseDelta() const {
		return m_mouseData.delta;
	}

	glm::vec2 Input::getMousePosition() const {
		return m_mouseData.position;
	}

	bool Input::isMouseButtonPressed(MouseButtonCode button) const {
		const auto it = buffer[m_parent].mouseButtons.find(button);
		const auto it2 = m_lastframeMouseButtons.find(button);
		return (it != buffer[m_parent].mouseButtons.end() && it->second) && !(it2 != m_lastframeMouseButtons.end() && it2->second);
	}

	bool Input::isMouseButtonDown(MouseButtonCode button) const {
		const auto it = buffer[m_parent].mouseButtons.find(button);
		return it != buffer[m_parent].mouseButtons.end() && it->second;
	}

	bool Input::isMouseButtonReleased(MouseButtonCode button) const {
		const auto it = buffer[m_parent].mouseButtons.find(button);
		const auto it2 = m_lastframeMouseButtons.find(button);
		return !(it != buffer[m_parent].mouseButtons.end() && it->second) && (it2 != m_lastframeMouseButtons.end() && it2->second);
	}

	bool Input::isKeyPressed(KeyCode key) const {
		const auto it = buffer[m_parent].keyboardKeys.find(key);
		const auto it2 = m_lastframeKeys.find(key);
		return (it != buffer[m_parent].keyboardKeys.end() && it->second) && !(it2 != m_lastframeKeys.end() && it2->second);
	}

	bool Input::isKeyDown(KeyCode key) const {
		const auto it = buffer[m_parent].keyboardKeys.find(key);
		return it != buffer[m_parent].keyboardKeys.end() && it->second;
	}

	bool Input::isKeyReleased(KeyCode key) const {
		const auto it = buffer[m_parent].keyboardKeys.find(key);
		const auto it2 = m_lastframeKeys.find(key);
		return !(it != buffer[m_parent].keyboardKeys.end() && it->second) && (it2 != m_lastframeKeys.end() && it2->second);
	}

	void Input::update(float deltatime) {
		m_lastframeKeys = buffer[m_parent].keyboardKeys;
		m_lastframeMouseButtons = buffer[m_parent].mouseButtons;

		double x, y;
		glfwGetCursorPos(m_parent, &x, &y);
		m_mouseData = MouseData{ glm::vec2(float(x), float(y)), (glm::vec2(float(x), float(y)) - m_mouseData.position) * deltatime };
	}

}