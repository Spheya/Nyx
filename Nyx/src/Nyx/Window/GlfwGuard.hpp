#pragma once

namespace Nyx {
	class GlfwGuard {
	public:
		GlfwGuard();
		~GlfwGuard();
		GlfwGuard(GlfwGuard&) = delete;
		GlfwGuard& operator=(GlfwGuard&) = delete;
		GlfwGuard(GlfwGuard&&);
		GlfwGuard& operator=(GlfwGuard&&);

	private:
		bool valid = true;
	};
}

