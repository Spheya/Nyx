#include "nyx_pch.hpp"
#include "GlfwGuard.hpp"

#include "GlfwIncludes.hpp"

namespace Nyx {
	GlfwGuard::GlfwGuard() {
		if (glfwInit()) {
			NYX_CORE_INFO("GLFW setup completed");
		} else {
			NYX_CORE_ERROR("GLFW setup failed");
		}
	}

	GlfwGuard::GlfwGuard(GlfwGuard&& other)
	{
		other.valid = false;
	}

	GlfwGuard& GlfwGuard::operator=(GlfwGuard&& other)
	{
		other.valid = false;
		return *this;
	}

	GlfwGuard::~GlfwGuard() {
		if (valid) {
			NYX_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}
}
