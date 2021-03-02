#pragma once

#include "Core/Base.hpp"

#include "Core/Debug.hpp"
#include "Core/Logger.hpp"

#include "Rendering/Renderer.hpp"

#include "Window/GlfwGuard.hpp"
#include "Window/Input.hpp"
#include "Window/Window.hpp"

#include "Maths.hpp"

#include "Window/Input.hpp"

namespace Nyx {

	[[nodiscard]] std::shared_ptr<Renderer> init() {

#ifdef NYX_DEBUG
		static bool first = true;

		if (!first)
			NYX_CORE_DEBUGBREAK("You can't call Nyx::init() multiple times!");

		first = false;
#endif

		Nyx::Logger::init();
		return std::make_shared<Renderer>();
	}
}