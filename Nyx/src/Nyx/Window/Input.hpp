#pragma once

#include <memory>
#include <unordered_map>
#include <atomic>

#include "Nyx/Maths.hpp"
#include "GlfwIncludes.hpp"
#include "KeyCodes.hpp"

//TODO: Just do this again, its very bad

namespace Nyx {
	class Input
	{
		friend class Window;
		friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	public:
		explicit Input(GLFWwindow* window);
		Input(Input&) = delete;
		Input& operator=(Input&) = delete;
		Input(Input&&) = default;
		Input& operator=(Input&&) = default;
		~Input() = default;

		void setParent(GLFWwindow* window);

		void enableLockedMouse(bool enable = true);
		void disableLockedMouse();
		[[nodiscard]] bool isMouseLocked() const;

		[[nodiscard]] glm::vec2 getMouseDelta() const;
		[[nodiscard]] glm::vec2 getMousePosition() const;

		[[nodiscard]] bool isMouseButtonPressed(MouseButtonCode button) const;
		[[nodiscard]] bool isMouseButtonDown(MouseButtonCode button) const;
		[[nodiscard]] bool isMouseButtonReleased(MouseButtonCode button) const;

		[[nodiscard]] bool isKeyPressed(KeyCode key) const;
		[[nodiscard]] bool isKeyDown(KeyCode key) const;
		[[nodiscard]] bool isKeyReleased(KeyCode key) const;

	private:
		struct MouseData {
			glm::vec2 position;
			glm::vec2 delta;
		};

		struct BufferData {
			std::unordered_map<KeyCode, bool> keyboardKeys;
			std::unordered_map<MouseButtonCode, bool> mouseButtons;
		};

		static std::unordered_map<GLFWwindow*, BufferData> buffer;

		std::unordered_map<KeyCode, bool> m_lastframeKeys;
		std::unordered_map<MouseButtonCode, bool> m_lastframeMouseButtons;

		MouseData m_mouseData;
		bool m_isMouseLocked = false;

		GLFWwindow* m_parent;

		void update(float deltatime);
	};
}