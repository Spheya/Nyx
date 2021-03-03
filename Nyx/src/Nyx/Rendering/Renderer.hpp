#pragma once

#include "Nyx/Window/GlfwGuard.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace Nyx {
	class Renderer
	{
	public:
		Renderer();

		void render();

	private:

		std::shared_ptr<Shader> m_raytracingShader;
		std::shared_ptr<VertexArray> m_blitMesh;
	};
}

