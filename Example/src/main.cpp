#include <Nyx/Nyx.hpp>

int main() {
	Nyx::init();
	auto context = std::make_shared<Nyx::RenderContext>("Nyx Demo", 640, 480);

	auto renderer = std::make_shared<Nyx::Renderer>();

	while (!context->getWindow().isCloseRequested()) {
		renderer->render();
		context->getWindow().update();
	}
}