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

#include "RenderContext.hpp"

namespace Nyx {

	void init() {
#ifdef NYX_ENABLE_ASSERTS
		static bool first = true;
		NYX_ASSERT(first, "You can't call Nyx::init() multiple times!");
#endif

		Nyx::Logger::init();
		NYX_INTERNAL_DISPLAY_DEBUGBREAK_WARNING
	}
}